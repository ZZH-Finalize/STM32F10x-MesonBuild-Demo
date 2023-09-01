#include "bitmap.h"
#include "util/value_ops.h"

bitmap_t* bitmap_init(bitmap_t* map, uint32_t max_num)
{
    CHECK_PTR(map, NULL);

    // up align to 32
    max_num = (max_num + 31) & ~31;

    map->buf = (uint32_t*)memAlloc(max_num / sizeof(*map->buf), 0);

    CHECK_PTR(map->buf, NULL);

    map->len = max_num / sizeof(*map->buf);

    return map;
}

bitmap_t* bitmap_create(uint32_t max_num)
{
    RETURN_IF_ZERO(max_num, NULL);
    bitmap_t* map = (bitmap_t*)memAlloc(sizeof(bitmap_t), 0);

    CHECK_PTR(map, NULL);

    if (NULL == bitmap_init(map, max_num)) {
        memFree(map);
        return NULL;
    }

    return map;
}

uint32_t bitmap_find_first_free(bitmap_t* map)
{
    BITMAP_CHECK_MAP(map, UINT32_MAX);

    const uint32_t bitmap_value_bits = sizeof(*map->buf) * 8;

    for (uint32_t i = 0; i < map->len; i++) {
        uint32_t value = map->buf[i];

        // ff0 algorithm - O(1) efficiency
        if (value < UINT32_MAX)  // has free bits
        {
            uint32_t bits_of_var = bitmap_value_bits;
            uint32_t bit_index = 0;

            while (bits_of_var != 0 && value != 0) {
                bits_of_var /= 2;
                uint32_t bits_half_mask = FILL_BITS(bits_of_var);

                // lower bytes are full
                if ((value & bits_half_mask) == bits_half_mask) {
                    bit_index += bits_of_var;
                    value >>= bits_of_var;  // take higher bytes
                }
            }

            return bit_index + i * bitmap_value_bits;
        }
    }

    return UINT32_MAX;
}
