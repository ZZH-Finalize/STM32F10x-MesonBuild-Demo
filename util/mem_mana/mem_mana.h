#ifndef __MEM_MANA_H__
#define __MEM_MANA_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "util/gnu_attributes.h"
#include "mem_pools.h"

#ifdef __cplusplus
extern "C" {
#endif

#define false   0
#define true    1
#define nullptr NULL

typedef struct __MemBlock
{
    struct __MemBlock *next, *prev;
    uint32_t size;
    uint8_t isFree;
    uint32_t mem[];
} MemBlock_t, *pMemBlock_t;

typedef struct
{
    MemBlock_t* const memStart;
    const void* const memEnd;
    uint32_t availableSize;
} MemPool_t, *pMemPool_t;

#define MemEnd(mem) (mem + ARRAY_SIZE(mem))
#define ArrayMem(arr)                     \
    {                                     \
        (pMemBlock_t) arr, MemEnd(arr), 0 \
    }

#define PoolByArray(pool, arr) [pool] = ArrayMem(arr)

void* memAlloc(size_t size, const uint32_t pool) GNU_ATTR(__malloc__);
void memFree(void* pMem);
bool memIsClean(const uint32_t pool);
bool memIsCleanAll(void);

#ifdef __cplusplus
}
#endif

#endif // __MEM_MANA_H__
