#ifndef __LINKED_LIST_COMMON_H__
#define __LINKED_LIST_COMMON_H__

#include <stdint.h>

#include "util/container_of.h"
#include "util/arg_checkers.h"
#include "list_iterators.h"

#define LL_NEXT_NODE(node) (node)->next
#define LL_PREV_NODE(node) (node)->prev

#endif // __LINKED_LIST_COMMON_H__
