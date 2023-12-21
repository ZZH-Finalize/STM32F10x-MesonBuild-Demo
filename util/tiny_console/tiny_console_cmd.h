#ifndef __TINY_CONSOLE_CMD_H__
#define __TINY_CONSOLE_CMD_H__

#include "tiny_console.h"
#include "util/gnu_attributes.h"

#define CONSOLE_CMD_DEF(name) \
    int name(console_t* this, const int argc, const console_cmd_arg_t* argv)

#define CONSOLE_CMD_UNUSE_ARGS \
    (void) this;               \
    (void) argc;               \
    (void) argv

#define CONSOLE_CMD_SECTION         .console.cmd
#define CONSOLE_BUILTIN_CMD_SECTION .console.builtin.cmd

#define EXPORT_CONSOLE_CMD_IN_SEC(sec, _cmd, _fn, _desc, _arg_desc, ...) \
    GNU_SECTION(sec)                                                     \
    const console_cmd_desc_t __console_cmd_desc_##_fn = {                \
        .cmd = _cmd,                                                     \
        .desc = _desc,                                                   \
        .fn = _fn,                                                       \
        .arg_desc = _arg_desc,                                            \
        ##__VA_ARGS__,                                                   \
    }

#define EXPORT_CONSOLE_CMD(cmd, fn, desc, arg_desc, ...)                    \
    EXPORT_CONSOLE_CMD_IN_SEC(CONSOLE_CMD_SECTION, cmd, fn, desc, arg_desc, \
                              ##__VA_ARGS__)

#if 1 == CONFIG_CONSOLE_BUILTIN_CMD_ENABLE
#define EXPORT_CONSOLE_BUILTIN_CMD(cmd, fn, desc, arg_desc, ...)          \
    EXPORT_CONSOLE_CMD_IN_SEC(CONSOLE_BUILTIN_CMD_SECTION, cmd, fn, desc, \
                              arg_desc, ##__VA_ARGS__)
#else
#define EXPORT_CONSOLE_BUILTIN_CMD(cmd, fn, desc, ...) \
    GNU_UNUSED console_cmd_desc_t* __ptr_to_##fn = NULL
#endif

#endif // __TINY_CONSOLE_CMD_H__
