#ifndef __LINKER_TOOLS_H__
#define __LINKER_TOOLS_H__

#include <stdint.h>
#include "util/gnu_attributes.h"

#define LINKER_SYMBOL_TYPE(sym, type) extern type sym[]
#define LINKER_SYMBOL8(sym)           LINKER_SYMBOL_TYPE(sym, uint8_t)
#define LINKER_SYMBOL16(sym)          LINKER_SYMBOL_TYPE(sym, uint16_t)
#define LINKER_SYMBOL32(sym)          LINKER_SYMBOL_TYPE(sym, uint32_t)

#define EXPORT_FUNC_WITH_LEVEL(fn, type, section, level) \
    GNU_ATTR(__section__("." #section "." #level))       \
    const type __##section##_ptr_to_##fn = fn

#define EXPORT_FUNC_WITH_NAME_LEVEL(fn, type, section, level)   \
    GNU_ATTR(__section__("." #section "." #level)) const struct \
    {                                                           \
        const char* name;                                       \
        type func;                                              \
    } __##section##_info_of_##fn = {.name = #fn, .func = fn}

#define EXPORT_ANY_FUNC_WITH_LEVEL(fn, section, level) \
    EXPORT_FUNC_WITH_LEVEL(fn, typeof(fn), section, level)

typedef void (*__init_call_fn_t)(void);

#define EXPORT_INIT_FUNC(fn, level) \
    EXPORT_FUNC_WITH_LEVEL(fn, __init_call_fn_t, init_func, level)

#endif // __LINKER_TOOLS_H__
