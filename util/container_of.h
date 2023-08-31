#ifndef __CONTAINER_OF_H__
#define __CONTAINER_OF_H__

#define offsetof(type, member) (&((type *)0)->member)
#define container_of(ptr, type, member) \
    (type *)((uint32_t)ptr - offsetof(type, member))

#endif  // __CONTAINER_OF_H__
