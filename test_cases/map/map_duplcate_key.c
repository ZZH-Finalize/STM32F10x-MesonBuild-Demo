#include "map_test_data.h"

static int map_duplcate_key_test(void* arg)
{
    (void)arg;
    const char* test_key = "test_key";

    int retv = 0;
    map_t* map = map_create(31, bkdr_hash);

    retv = map_insert(map, test_key, 141516);
    RETURN_IF_NZERO(retv, retv);

    map_value_t res_value = 0;

    retv = map_search(map, test_key, &res_value);
    RETURN_IF_NZERO(retv, retv);
    RETURN_IF(res_value != 141516, -EINVAL);

    retv = map_insert(map, test_key, 141518);
    RETURN_IF_NZERO(retv, retv);

    retv = map_search(map, test_key, &res_value);
    RETURN_IF_NZERO(retv, retv);
    RETURN_IF(res_value != 141518, -EINVAL);

    map_delete(map);

    return 0;
}
EXPORT_TEST_CASE(map_duplcate_key_test);
