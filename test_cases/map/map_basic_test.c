#include "test_frame.h"
#include "util/arg_checkers.h"
#include "util/hash/str_hash.h"
#include "util/map/map.h"
#include "util/iterators.h"

typedef struct
{
    uint32_t val;
    char key[64];
} test_data_t;

static test_data_t test_data[10];

int map_basic_test(void *arg)
{
    map_t *map = map_create(31, bkdr_hash);
    CHECK_PTR(map, -ENOMEM);

    srand(rand());

    ITER_ARRAY(iter, test_data)
    {
        ITER_ARRAY(key_iter, iter->key)
        {
            *key_iter = rand() % 127 + 32;
        }
        iter->val = (uint32_t)rand();
        int retv = map_insert(map, iter->key, iter->val);
        RETURN_IF_NZERO(retv, -EINVAL);
    }

    ITER_ARRAY(iter, test_data)
    {
        uint32_t search_res = 0;
        int retv = map_search(map, iter->key, &search_res);
        RETURN_IF_NZERO(retv, -EINVAL);
        RETURN_IF(search_res != iter->val, -EINVAL);
    }

    return 0;
}
EXPORT_TEST_CASE(map_basic_test);
