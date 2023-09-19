#ifndef __HASH_ALL_TEST_H__
#define __HASH_ALL_TEST_H__

#include "test_cases.h"
#include "util/hash/str_hash.h"

typedef struct
{
    const char* name;
    str_hash_t func;
} hash_func_table_t;

void str_hash_demo(void);

#endif // __HASH_ALL_TEST_H__
