#ifndef __MEM_ALLOC_H__
#define __MEM_ALLOC_H__

#include <stdint.h>

typedef struct memblock_header_t
{
    struct memblock_header_t* prev;

    uint32_t size;

    union
    {
        struct
        {
            uint8_t free : 1;
        } bits;

        uint8_t value;
    } flags;

    uint32_t mem[];

} memblock_header_t __attribute__((__aligned__(4)));

typedef struct
{
    memblock_header_t* start_address;
    uint32_t pool_size;
} mempool_t;

void* mem_alloc(uint32_t size, uint32_t pool_idx);
void mem_free(void* pmem, uint32_t pool_idx);

#endif  // __MEM_ALLOC_H__
