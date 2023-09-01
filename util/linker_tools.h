#ifndef __LINKER_TOOLS_H__
#define __LINKER_TOOLS_H__

#include <stdint.h>

#define LINKER_SYMBOL_TYPE(sym, type) extern type sym[]
#define LINKER_SYMBOL8(sym)           LINKER_SYMBOL_TYPE(sym, uint8_t)
#define LINKER_SYMBOL16(sym)          LINKER_SYMBOL_TYPE(sym, uint16_t)
#define LINKER_SYMBOL32(sym)          LINKER_SYMBOL_TYPE(sym, uint32_t)

typedef void (*__init_call_fn_t)(void);

#define EXPORT_INIT_FUNC(fn, level)                    \
    __attribute__((__section__(".init_func." #level))) \
    const __init_call_fn_t __init_func_ptr_to_##fn = fn

#endif  // __LINKER_TOOLS_H__
