#ifndef __MAP_H__
#define __MAP_H__

#include <stdint.h>
#include "util/linked_list/linked_list.h"
#include "util/mem_mana/mem_mana.h"
#include "util/hash/str_hash.h"

typedef const char* map_key_t;
typedef size_t map_value_t;
typedef void (*map_foreach_cb_t)(map_key_t key, map_value_t value);

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
    uint32_t mem_pool;
    str_hash_t hash;
    map_item_list_t items[];
} map_t;

/*
@brief create a map in the specific memory pool
@param mod_value - should be a prime number to reduce hash conflict
@param hash_cb - hash method
@param pool - the memory pool id
@return map_t
*/
map_t* map_create_in_pool(uint32_t mod_value, str_hash_t hash_cb,
                          uint32_t pool);

/*
@brief create a map
@param mod_value - should be a prime number to reduce hash conflict
@param hash_cb - hash method
@return map_t
*/
static inline map_t* map_create(uint32_t mod_value, str_hash_t hash_cb)
{
    return map_create_in_pool(mod_value, hash_cb, MEMPOOL_DEFAULT);
}

/**
 * @brief insert a key-value pair into a map
 *
 * @param this - map_t struct
 * @param key - a string
 * @param value - size_t value or a pointer
 * @return int == 0: succ, < 0: fail
 */
int map_insert(map_t* this, map_key_t key, map_value_t value);

/**
 * @brief search the node which match with the given key
 *
 * @param this - map_t struct
 * @param key - a string
 * @param res - searched node
 * @return int == 0: succ, < 0: fail
 */
int map_search(map_t* this, map_key_t key, map_value_t* res);

/**
 * @brief remove the node which has the given key
 *
 * @param this - map_t struct
 * @param key - a string
 * @return int == 0: succ, < 0: fail
 */
int map_remove(map_t* this, map_key_t key);

/**
 * @brief clear the map, which will delete all nodes
 *
 * @param this - map_t struct
 */
void map_clear(map_t* this);

/**
 * @brief delete a map
 *
 * @param this - map_t struct
 */
static inline void map_delete(map_t* this)
{
    map_clear(this);
    memFree(this);
}

/**
 * @brief iterate all map with a callback
 *
 * @param this - map_t struct
 * @param cb - callback function
 */
void map_foreach(map_t* this, map_foreach_cb_t cb);

#endif // __MAP_H__
