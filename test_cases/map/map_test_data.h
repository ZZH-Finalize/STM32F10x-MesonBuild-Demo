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

test_data_t *generate_test_data(uint32_t size);

static inline void release_test_data(void *data)
{
    memFree(data);
}
