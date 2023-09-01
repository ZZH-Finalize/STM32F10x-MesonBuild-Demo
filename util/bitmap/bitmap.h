#ifndef __BIT_MAP_H__
#define __BIT_MAP_H__

#include <stdint.h>
#include <string.h>
#include "util/iterators.h"
#include "util/arg_checkers.h"
#include "util/mem_mana/mem_mana.h"

#define BITMAP_CHECK_MAP(map, retv) \
    CHECK_PTR(map, retv);           \
    CHECK_PTR(map->buf, retv)

typedef struct
{
    uint32_t* buf;
    uint32_t len;
} bitmap_t;

bitmap_t* bitmap_init(bitmap_t* map, uint32_t max_num);

static inline void bitmap_init_static(bitmap_t* map, uint32_t* val_buf,
                                      uint32_t buf_size)
{
    CHECK_PTR(map, );

    map->buf = val_buf;
    map->len = buf_size / sizeof(*map->buf);
}

bitmap_t* bitmap_create(uint32_t max_num);

static inline void bitmap_deinit(bitmap_t* map)
{
    CHECK_PTR(map, );

    memFree(map->buf);
    map->buf = NULL;
    map->len = 0;
}

static inline void bitmap_delete(bitmap_t* map)
{
    CHECK_PTR(map, );

    bitmap_deinit(map);
    memFree(map);
}

static inline uint32_t bitmap_resize(bitmap_t* map, uint32_t new_size)
{
    CHECK_PTR(map, 0);

    bitmap_deinit(map);
    bitmap_init(map, new_size);
}

static inline void bitmap_clear(bitmap_t* map)
{
    BITMAP_CHECK_MAP(map, );

    memset(map->buf, 0, map->len * sizeof(*map->buf));
}

void bitmap_save(bitmap_t* map, uint32_t value)
{
    BITMAP_CHECK_MAP(map, );

    uint32_t unit_index = value / (sizeof(*map->buf) * 8);
    uint32_t bit_index = value % (sizeof(*map->buf) * 8);

    if (unit_index < map->len)
        map->buf[unit_index] |= 1 << bit_index;
}

void bitmap_drop(bitmap_t* map, uint32_t value)
{
    BITMAP_CHECK_MAP(map, );

    uint32_t unit_index = value / (sizeof(*map->buf) * 8);
    uint32_t bit_index = value % (sizeof(*map->buf) * 8);

    if (unit_index < map->len)
        map->buf[unit_index] &= ~(1 << bit_index);
}

uint8_t bitmap_check(bitmap_t* map, uint32_t value)
{
    BITMAP_CHECK_MAP(map, 0);

    uint32_t unit_index = value / (sizeof(*map->buf) * 8);
    uint32_t bit_index = value % (sizeof(*map->buf) * 8);
    uint32_t bit_mask = 1 << bit_index;

    if (unit_index < map->len)
        return (map->buf[unit_index] & bit_mask) == bit_mask;

    return 0;
}

uint32_t bitmap_find_first_free(bitmap_t* map);

#endif  // __BIT_MAP_H__
