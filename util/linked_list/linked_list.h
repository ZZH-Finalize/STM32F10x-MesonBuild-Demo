#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "linked_list_common.h"

typedef struct __list_node_t
{
    struct __list_node_t *next;
} list_node_t;

// return any negative value will stop foreach
typedef int (*list_foreach_cb)(list_node_t *);

static inline int list_foreach(list_node_t *head, list_foreach_cb callback)
{
    CHECK_PTR(head, -EINVAL);

    ITER_LIST (node, head) {
        int cb_retv = callback(node);
        RETURN_IF(cb_retv != 0, cb_retv);
    }

    return 0;
}

static inline uint32_t list_length(list_node_t *head)
{
    CHECK_PTR(head, 0);

    uint32_t len = 0;

    ITER_LIST (_, head) len++;

    return len;
}

static inline list_node_t *list_find_last_node(list_node_t *head)
{
    CHECK_PTR(head, NULL);

    while (NULL != head->next) head = head->next;

    return head;
}

static inline list_node_t *list_index(list_node_t *head, uint32_t index)
{
    CHECK_PTR(head, NULL);

    list_node_t *node = head;

    while (0 != index-- && NULL != node) node = node->next;

    return node;
}

static inline void list_append(list_node_t *head, list_node_t *chain)
{
    CHECK_PTR(head, );
    CHECK_PTR(chain, );

    list_node_t *tail = list_find_last_node(head);
    tail->next = chain;
}

static inline void list_insert(list_node_t *insert_head, list_node_t *chain)
{
    CHECK_PTR(insert_head, );
    CHECK_PTR(chain, );

    list_node_t *head_next = insert_head->next;
    insert_head->next = chain;

    list_node_t *chain_tail = list_find_last_node(chain);
    chain_tail->next = head_next;
}

static inline void list_remove(list_node_t *head, list_node_t *node)
{
    CHECK_PTR(head, );
    CHECK_PTR(node, );

    while (node != head->next && head != NULL) head = head->next;

    CHECK_PTR(head, );

    head->next = node->next;
}

#endif // __LINKED_LIST_H__
