#include "test_frame.h"
#include "util/tiny_console/tiny_console_cmd.h"
#include "util/iterators.h"

CONSOLE_CMD_DEF(run_all_testcases_warp)
{
    CONSOLE_CMD_UNUSE_ARGS;

    uint32_t all_num = get_all_testcases_num();
    uint32_t succ_num = run_all_testcases(NULL);

    console_send_str(this, "test result: \r\n");
    console_printf(this, "passed [%ld/%ld]\r\n", succ_num, all_num);
    console_printf(this, "failed [%ld/%ld]\r\n", all_num - succ_num, all_num);

    return all_num == succ_num ? 0 : -EINVAL;
}
EXPORT_CONSOLE_CMD("run_tc", run_all_testcases_warp, "Run all testcases");

CONSOLE_CMD_DEF(run_all_demo_warp)
{
    CONSOLE_CMD_UNUSE_ARGS;

    console_printf(this, "argc: %d\r\n", argc);

    FOR_I((uint32_t)argc)
    {
        console_printf(this, "arg[%ld]: %s\n", i, argv[i]);
    }

    run_all_demo();

    return 0;
}
EXPORT_CONSOLE_CMD("run_demo", run_all_demo_warp, "Run all demo");
