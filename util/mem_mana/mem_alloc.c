#include "mem_alloc.h"
#include "util/container_of.h"
#include "util/linker_tools.h"

#define MK_MEM_POOL(addr, size)                                        \
    {                                                                  \
        .start_address = (memblock_header_t *)addr, .pool_size = size, \
    }

#define MK_MEM_POOL_BY_ARRAY(arr) MK_MEM_POOL(arr, sizeof(arr))

// clang-format off
static const mempool_t mem_pools[] = {
    MK_MEM_POOL(0x20000000, 128),
};
// clang-format on
