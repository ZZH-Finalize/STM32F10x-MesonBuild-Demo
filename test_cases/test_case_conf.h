#ifndef __TEST_CASE_CONF_H__
#define __TEST_CASE_CONF_H__

#include "util/linker_tools.h"

typedef int (*__test_case_fn_t)(void *arg);
typedef void (*__demo_fn_t)(void);

typedef struct
{
    const char *name;
    __test_case_fn_t fn;
} __test_case_info_t;

#if CONFIG_ENABLE_TEST_CASES == 1
#define EXPORT_TEST_CASE_LEVEL(fn, level) \
    EXPORT_FUNC_WITH_NAME_LEVEL(fn, __test_case_fn_t, test_cases, level)
#else
#define EXPORT_TEST_CASE_LEVEL(fn, level) \
    GNU_UNUSED __test_case_fn_t __ptr_to_##fn##_##level = fn
#endif

#if CONFIG_ENABLE_DEMO == 1
#define EXPORT_DEMO_LEVEL(fn, level) \
    EXPORT_FUNC_WITH_LEVEL(fn, __demo_fn_t, demo, level)
#else
#define EXPORT_DEMO_LEVEL(fn, level) \
    GNU_UNUSED __demo_fn_t __ptr_to_##fn##_##level = fn
#endif

#define EXPORT_TEST_CASE(fn) EXPORT_TEST_CASE_LEVEL(fn, 9)
#define EXPORT_DEMO(fn)      EXPORT_DEMO_LEVEL(fn, 9)

#endif // __TEST_CASE_CONF_H__
