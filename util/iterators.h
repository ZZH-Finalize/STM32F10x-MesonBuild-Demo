#ifndef __ITERATORS_H__
#define __ITERATORS_H__

#define FOR(var, num)       for (uint32_t var = 0; var < num; var++)
#define FOR_I(num)          FOR (i, num)
#define FOR_J(num)          FOR (j, num)
#define FOR_K(num)          FOR (k, num)

#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof(*arr))
#define FOR_ARRAY(var, arr) FOR (var, ARRAY_SIZE(arr))
#define FOR_ARRAY_I(arr)    FOR_I (ARRAY_SIZE(arr))
#define FOR_ARRAY_J(arr)    FOR_J (ARRAY_SIZE(arr))
#define FOR_ARRAY_K(arr)    FOR_K (ARRAY_SIZE(arr))
#define ITER_ARRAY(iter_name, arr)                                             \
    for (typeof(*arr) *iter_name = &arr[0]; iter_name < &arr[ARRAY_SIZE(arr)]; \
         iter_name++)

#endif // __ITERATORS_H__
