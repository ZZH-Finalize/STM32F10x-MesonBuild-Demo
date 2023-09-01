#include "mem_alloc.h"
#include "mem_conf.h"
#include "util/container_of.h"
#include "util/linker_tools.h"
#include "util/iterators.h"

#include <stdlib.h>

#define MK_MEM_POOL(addr, size)                                        \
    {                                                                  \
        .start_address = (memblock_header_t *)addr, .pool_size = size, \
    }

#define MK_MEM_POOL_BY_ARRAY(arr) MK_MEM_POOL(arr, sizeof(arr))

#define PREV_BLOCK(blk)           (blk->prev)
#define NEXT_BLOCK(blk) \
    (typeof(blk))((uint32_t)blk + blk->size + sizeof(memblock_header_t))

uint32_t default_pool[DEFAULT_POOL_SIZE * 1024 / 4];

static const mempool_t mem_pools[] = {
    MK_MEM_POOL_BY_ARRAY(default_pool),
};

void mem_init(void)
{
    ITER_ARRAY(ppool, mem_pools)
    {
        memblock_header_t *pheader = ppool->start_address;

        pheader->size = ppool->pool_size - sizeof(*pheader);
        pheader->flags.bits.free = 1;
        pheader->prev = NULL;
    }
}
EXPORT_INIT_FUNC(mem_init, 9);

void *mem_alloc(uint32_t size, uint32_t pool_idx)
{
    if (pool_idx >= ARRAY_SIZE(mem_pools))
        return NULL;

    const mempool_t *pool = &mem_pools[pool_idx];

    if (NULL == pool)
        return NULL;

    // align to 4
    size = (size & 0xFFFFFFFC) + ((0 != (size % 4)) * 4);

    memblock_header_t *pheader = pool->start_address;
    memblock_header_t *pend =
        (memblock_header_t *)((uint32_t)pool->start_address + pool->pool_size);

    while (pheader < pend) {
        // can be allocated
        if (1 == pheader->flags.bits.free && size <= pheader->size) {
            // alloc a new block
            memblock_header_t *pnext = (memblock_header_t *)((uint32_t)pheader +
                                       size + sizeof(*pheader));
            pnext->size = pheader->size - size - sizeof(*pnext);
            pnext->flags.bits.free = 1;
            pnext->prev = pheader;
            pheader->size = size;
            pheader->flags.bits.free = 0;

            return pheader->mem;
        } else {
            // check the next block
            pheader = NEXT_BLOCK(pheader);
        }
    }

    return NULL;
}

void mem_free(void *pmem, uint32_t pool_idx)
{
    if (pool_idx >= ARRAY_SIZE(mem_pools))
        return;

    const mempool_t *pool = &mem_pools[pool_idx];

    if (NULL == pool)
        return;

    // does not belong to this pool
    if (pmem <= (void *)pool->start_address ||
        pmem >= (void *)((uint32_t)pool->start_address + pool->pool_size))
        return;

    memblock_header_t *header = container_of(pmem, memblock_header_t, mem);
    memblock_header_t *prev = PREV_BLOCK(header);
    memblock_header_t *next = NEXT_BLOCK(header);

    // combine free block after this
    if (NULL != next && 1 == next->flags.bits.free) {
        // combine memsize
        header->size += next->size + sizeof(*next);

        memblock_header_t *nnext = NEXT_BLOCK(next);

        if (NULL != nnext)  // skip next to free it
        {
            nnext->prev = header;
            // update local next variable
            next = nnext;
        }
    }

    // combine free block before this
    if (NULL != prev && 1 == prev->flags.bits.free) {
        // combine memsize
        prev->size += header->size + sizeof(*header);

        if (NULL != next)
            next->prev = prev;
    }

    header->flags.bits.free = 1;
}
