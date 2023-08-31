#ifndef __MEM_ALLOC_H__
#define __MEM_ALLOC_H__

#include <stdint.h>

typedef struct
{
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

} memblock_header_t;

typedef struct
{
    memblock_header_t* start_address;
    uint32_t pool_size;
} mempool_t;

#endif  // __MEM_ALLOC_H__
