#ifndef __MAP_H__
#define __MAP_H__

#include <stdint.h>
#include "util/linked_list/linked_list.h"
#include "util/mem_mana/mem_mana.h"
#include "util/hash/str_hash.h"

#define MAP_MEMPOOL 0

typedef const char* map_key_t;
typedef size_t map_value_t;

typedef struct
{
    list_node_t node;

    map_key_t key;
    map_value_t value;
} map_item_t;

typedef struct
{
    map_item_t item;
    uint32_t length;
} map_item_list_t;

typedef struct
{
    uint32_t mod_value;
    str_hash_t hash;
    map_item_list_t items[];
} map_t;

/*
@brief create a map
@param mod_value - should be a prime number to reduce hash conflict
@param hash_cb - hash method
@return map_t
*/
map_t* map_create(uint32_t mod_value, str_hash_t hash_cb);

int map_insert(map_t* this, map_key_t key, map_value_t value);
int map_search(map_t* this, map_key_t key, map_value_t* res);
int map_remove(map_t* this, map_key_t key);
void map_clear(map_t* this);

static inline void map_delete(map_t* this)
{
    map_clear(this);
    memFree(this);
}

#endif  // __MAP_H__
