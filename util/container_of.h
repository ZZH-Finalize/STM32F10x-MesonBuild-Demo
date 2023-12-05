#ifndef __CONTAINER_OF_H__
#define __CONTAINER_OF_H__

#include <stddef.h>

#define container_of(ptr, type, member) \
    (type *) ((size_t) ptr - offsetof(type, member))

#endif // __CONTAINER_OF_H__
