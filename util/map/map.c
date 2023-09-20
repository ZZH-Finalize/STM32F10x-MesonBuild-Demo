#include <string.h>
#include "map.h"
#include "util/iterators.h"
#include "util/container_of.h"
#include "util/linked_list/list_iterators.h"
#include "util/gnu_attributes.h"

GNU_UNUSED static map_key_t dup_key(map_key_t key)
{
    CHECK_PTR(key, NULL);

    uint32_t key_len = 0;
    for (map_key_t pk = key; *pk != '\0'; pk++)
        key_len++;

    char* new_key = (char*)memAlloc(key_len + 1, MAP_MEMPOOL);
    CHECK_PTR(new_key, NULL);
    strcpy(new_key, key);
    return new_key;
}

static map_item_t* search_node(map_item_list_t* item_list, map_key_t key)
{
    CHECK_PTR(item_list, NULL);
    CHECK_PTR(key, NULL);

    // if there is no any node, then it can't be found
    // if have some nodes, then check every one
    if (0 != item_list->length) {
        ITER_LIST(iter, &item_list->item.node)
        {
            map_item_t* item = container_of(iter, map_item_t, node);
            if (NULL != item->key) {
                if (0 == strcmp(item->key, key)) {
                    return item;
                }
            }
        }
    }

    return NULL;
}

map_t* map_create(uint32_t mod_value, str_hash_t hash_cb)
{
    RETURN_IF(mod_value < 2, NULL);
    CHECK_PTR(hash_cb, NULL);

    map_t* tmp = memAlloc(sizeof(map_t) + sizeof(map_item_list_t) * mod_value,
                          MAP_MEMPOOL);
    CHECK_PTR(tmp, NULL);

    tmp->mod_value = mod_value;
    tmp->hash = hash_cb;

    FOR_I(mod_value)
    {
        tmp->items[i].item.node.next = NULL;
        tmp->items[i].length = 0;
    }

    return tmp;
}

int map_insert(map_t* this, map_key_t key, map_value_t value)
{
    CHECK_PTR(this, -EINVAL);
    CHECK_PTR(key, -EINVAL);

    map_key_t new_key = key;

    uint32_t hash_val = this->hash(new_key) % this->mod_value;
    map_item_list_t* item_list = &this->items[hash_val];

    map_item_t* item = search_node(item_list, key);

    if (NULL == item) {                // not a duplicate key
        if (0 == item_list->length) {  // first node of this list
            item_list->item.key = new_key;
            item_list->item.value = value;
        } else {  // from second node start, we need to alloc new node
            map_item_t* new_item = memAlloc(sizeof(map_item_t), MAP_MEMPOOL);
            CHECK_PTR(new_item, -ENOMEM);
            new_item->key = new_key;
            new_item->value = value;
            list_append(&item_list->item.node, &new_item->node);
        }

        item_list->length++;
    } else {  // for duplicate key, just modify the value
        item->value = value;
    }

    return 0;
}

int map_search(map_t* this, map_key_t key, map_value_t* res)
{
    CHECK_PTR(this, -EINVAL);
    CHECK_PTR(res, -EINVAL);

    uint32_t hash_val = this->hash(key) % this->mod_value;
    map_item_list_t* item_list = &this->items[hash_val];

    map_item_t* item = search_node(item_list, key);

    CHECK_PTR(item, -EEXIST);

    *res = item->value;

    return 0;
}

int map_remove(map_t* this, map_key_t key)
{
    CHECK_PTR(this, -EINVAL);
    uint32_t hash_val = this->hash(key) % this->mod_value;
    map_item_list_t* item_list = &this->items[hash_val];

    map_item_t* item = search_node(item_list, key);

    CHECK_PTR(item, -ENODATA);

    // the item to be deleted is the head, which is not a allocted node
    if (item == &item_list->item) {
        item->key = NULL;
    } else {  // item is a allocated node, then just delete it
        list_remove(&item_list->item.node, &item->node);
        memFree(item);
    }

    item_list->length--;

    return 0;
}

void map_clear(map_t* this)
{
    CHECK_PTR(this, );

    FOR_I(this->mod_value)
    {
        map_item_list_t* item_list = &this->items[i];
        if (item_list->length > 1) {
            list_node_t* node = LL_NEXT_NODE(&item_list->item.node);

            while (NULL != node) {
                list_node_t* next = node->next;
                memFree(container_of(node, map_item_t, node));
                node = next;
            }
        }

        item_list->item.key = NULL;
    }
}
