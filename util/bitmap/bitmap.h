#ifndef __BIT_MAP_H__
#define __BIT_MAP_H__

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "util/iterators.h"
#include "util/arg_checkers.h"
#include "util/mem_mana/mem_mana.h"

#define BITMAP_CHECK_MAP(map, retv) \
    CHECK_PTR(map, retv);           \
    CHECK_PTR(map->buf, retv)

typedef struct
{
    uint32_t len;
    uint32_t buf[];
} bitmap_t;

/**
 * @brief create a bit map in the specific memory pool
 *
 * @param max_num - maximun value
 * @param pool - memory pool id
 * @return bitmap_t* - created bitmap
 */
bitmap_t* bitmap_create_in_pool(uint32_t max_num, uint32_t pool);

/**
 * @brief create a bit map
 *
 * @param max_num - maximun value
 * @return bitmap_t* - created bitmap
 */
static inline bitmap_t* bitmap_create(uint32_t max_num)
{
    return bitmap_create_in_pool(max_num, MEMPOOL_DEFAULT);
}

/**
 * @brief delete a bitmap
 *
 * @param map
 */
static inline void bitmap_delete(bitmap_t* map)
{
    memFree(map);
}

/**
 * @brief clear a bitmap
 *
 * @param map - bitmap_t struct
 */
static inline void bitmap_clear(bitmap_t* map)
{
    BITMAP_CHECK_MAP(map, );

    memset(map->buf, 0, map->len * sizeof(*map->buf));
}

/**
 * @brief save a value in given bitmap
 *
 * @param map - bitmap_t struct
 * @param value - value to be saved
 */
static inline void bitmap_save(bitmap_t* map, uint32_t value)
{
    BITMAP_CHECK_MAP(map, );

    uint32_t unit_index = value / (sizeof(*map->buf) * 8);
    uint32_t bit_index = value % (sizeof(*map->buf) * 8);

    if (unit_index < map->len)
        map->buf[unit_index] |= 1 << bit_index;
}

/**
 * @brief delete a value from the given bitmap
 *
 * @param map - bitmap_t struct
 * @param value - value to be deleted
 */
static inline void bitmap_drop(bitmap_t* map, uint32_t value)
{
    BITMAP_CHECK_MAP(map, );

    uint32_t unit_index = value / (sizeof(*map->buf) * 8);
    uint32_t bit_index = value % (sizeof(*map->buf) * 8);

    if (unit_index < map->len)
        map->buf[unit_index] &= ~(1 << bit_index);
}

/**
 * @brief check the given value is exist in the bitmap or not
 *
 * @param map - bitmap_t struct
 * @param value - value to be check
 * @return bool true: exist, false: not exsit
 */
static inline bool bitmap_check(bitmap_t* map, uint32_t value)
{
    BITMAP_CHECK_MAP(map, 0);

    uint32_t unit_index = value / (sizeof(*map->buf) * 8);
    uint32_t bit_index = value % (sizeof(*map->buf) * 8);
    uint32_t bit_mask = 1 << bit_index;

    if (unit_index < map->len)
        return (map->buf[unit_index] & bit_mask) == bit_mask;

    return 0;
}

/**
 * @brief find the first value in given bitmap
 *
 * @param map - bitmap_t struct
 * @return uint32_t first freed value
 */
uint32_t bitmap_find_first_free(bitmap_t* map);

#endif // __BIT_MAP_H__
