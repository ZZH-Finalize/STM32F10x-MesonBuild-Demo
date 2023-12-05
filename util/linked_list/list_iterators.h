#ifndef __LIST_ITERATORS_H__
#define __LIST_ITERATORS_H__

#include <stddef.h>

#define ITER_LIST(iter_name, head)                         \
    for (typeof(head) iter_name = head; NULL != iter_name; \
         iter_name = iter_name->next)

#endif // __LIST_ITERATORS_H__
