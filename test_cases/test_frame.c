#include <stdlib.h>
#include "test_frame.h"
#include "util/iterators.h"

LINKER_SYMBOL_TYPE(__stest_cases, __test_case_fn_t);
LINKER_SYMBOL_TYPE(__etest_cases, __test_case_fn_t);

LINKER_SYMBOL_TYPE(__sdemo, __demo_fn_t);
LINKER_SYMBOL_TYPE(__edemo, __demo_fn_t);

int run_all_testcases(void* arg)
{
    uint32_t succ_count = 0;
    uint32_t test_case_num =
        ((uint32_t)__etest_cases - (uint32_t)__stest_cases) / 4;

    FOR_I(test_case_num)
    {
        succ_count += (0 == __stest_cases[i](arg));
    }

    return succ_count;
}

void run_all_demo(void)
{
    uint32_t demo_num = ((uint32_t)__edemo - (uint32_t)__sdemo) / 4;

    FOR_I(demo_num)
    {
        __sdemo[i]();
    }
}
