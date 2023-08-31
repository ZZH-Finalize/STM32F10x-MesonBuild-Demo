#ifndef __CONTAINER_OF_H__
#define __CONTAINER_OF_H__

#define offsetof(type, member) (&((type *)0)->member)
#define container_of(ptr, type, member)                    \
    ({                                                     \
        const typeof(((type *)0)->member) *__mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member)); \
    })

#endif  // __CONTAINER_OF_H__
