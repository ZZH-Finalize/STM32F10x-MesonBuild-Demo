#include "map_test_data.h"

static int map_delete_test(void *arg)
{
    (void)arg;

    test_data_t *test_data = generate_test_data(TEST_DATA_SIZE);
    map_t *map = map_create_in_pool(31, bkdr_hash, CONFIG_CHECK_TESTCASE_MEMPOOL);

    FOR_I(TEST_DATA_SIZE)
    {
        test_data_t *iter = &test_data[i];
        int retv = map_insert(map, iter->key, iter->val);
        RETURN_IF_NZERO(retv, retv);
    }

    FOR_I(TEST_DATA_SIZE)
    {
        test_data_t *iter = &test_data[i];
        int retv = map_remove(map, iter->key);
        RETURN_IF_NZERO(retv, retv);
    }

    release_test_data(test_data);
    map_delete(map);

    return 0;
}
EXPORT_TEST_CASE(map_delete_test);
