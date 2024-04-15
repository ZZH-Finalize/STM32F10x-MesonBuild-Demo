#include "test_case_conf.h"
#include "test_cases/test_frame.h"
#include "tiny_console/tiny_console.h"
#include "tiny_console/tiny_console_cmd.h"
#include <stdarg.h>
#include "iterators.h"

#if CONFIG_ENABLE_TEST_CASES == 1

static console_t* __dbg_console = NULL;

static int print(const char *fmt, ...)
{
    va_list vargs;
    va_start(vargs, fmt);
    int len = console_vprintf(__dbg_console, fmt, vargs);
    va_end(vargs);

    return len;
}

CONSOLE_CMD_DEF(run_all_testcases_warp)
{
    CONSOLE_CMD_UNUSE_ARGS;

    test_case_arg_t arg = {
        .args = NULL,
        .print = print
    };

    uint32_t all_num = get_all_testcases_num();
    uint32_t succ_num = run_all_testcases(&arg);

    console_send_strln(this, "test result: ");
    console_println(this, "passed [%ld/%ld]", succ_num, all_num);
    console_println(this, "failed [%ld/%ld]", all_num - succ_num, all_num);

    return all_num == succ_num ? 0 : -EINVAL;
}

EXPORT_CONSOLE_CMD("run_tc", run_all_testcases_warp, "Run all testcases", NULL);

#endif

#if CONFIG_ENABLE_DEMO == 1

CONSOLE_CMD_DEF(run_all_demo_warp)
{
    CONSOLE_CMD_UNUSE_ARGS;

    run_all_demo();

    return 0;
}

EXPORT_CONSOLE_CMD("run_demo", run_all_demo_warp, "Run all demo", NULL);

#endif

CONSOLE_CMD_DEF(test)
{
    CONSOLE_CMD_UNUSE_ARGS;

    console_println(this, "argc: %d", argc);
    console_println(this, "argv[0]: %lu", argv[0].unum);
    console_println(this, "argv[1]: %lu", argv[1].unum);
    console_println(this, "argv[2]: %s", argv[2].str);
    console_println(this, "argv[3]: %lu", argv[3].unum);

    if (argc > 4) {
        console_println(this, "argv[4]: %lu", (uint32_t) argv[4].unum);
    }

    if (argc > 5) {
        console_println(this, "argv[5]: %s", argv[5].str);
    }

    return 0;
}

EXPORT_CONSOLE_CMD("test", test, "test the console command", "ddsd[ds]");
