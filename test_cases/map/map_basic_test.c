#include "test_frame.h"
#include "util/arg_checkers.h"
#include "util/hash/str_hash.h"
#include "util/map/map.h"
#include "util/iterators.h"

#define TEST_DATA_SIZE 32

typedef struct
{
    map_value_t val;
    char key[24];
} test_data_t;

int map_basic_test(void *arg)
{
    map_t *map = map_create(31, bkdr_hash);
    CHECK_PTR(map, -ENOMEM);

    srand(rand());

    test_data_t *test_data =
        (test_data_t *)memAlloc(sizeof(test_data_t) * TEST_DATA_SIZE, 0);

    CHECK_PTR(test_data, -ENOMEM);

    FOR_I(TEST_DATA_SIZE)
    {
        test_data_t *iter = &test_data[i];
        ITER_ARRAY(key_iter, iter->key)
        {
            *key_iter = rand() % 95 + 32;
        }
        iter->key[sizeof(iter->key) - 1] = '\0';

        iter->val = (map_value_t)rand();
        int retv = map_insert(map, iter->key, iter->val);
        RETURN_IF_NZERO(retv, retv);
    }

    FOR_I(TEST_DATA_SIZE)
    {
        test_data_t *iter = &test_data[i];
        map_value_t search_res = 0;
        int retv = map_search(map, iter->key, &search_res);
        RETURN_IF_NZERO(retv, retv);
        RETURN_IF(search_res != iter->val, -EINVAL);
    }

    memFree(test_data);

    return 0;
}
EXPORT_TEST_CASE(map_basic_test);
