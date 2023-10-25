#include "map_test_data.h"

static int map_basic_test(void *arg)
{
    (void)arg;
    map_t *map = map_create_in_pool(31, bkdr_hash, CONFIG_CHECK_TESTCASE_MEMPOOL);
    CHECK_PTR(map, -ENOMEM);

    srand(rand());

    test_data_t *test_data = generate_test_data(TEST_DATA_SIZE);

    FOR_I(TEST_DATA_SIZE)
    {
        test_data_t *iter = &test_data[i];
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

    release_test_data(test_data);
    map_delete(map);

    return 0;
}
EXPORT_TEST_CASE(map_basic_test);
