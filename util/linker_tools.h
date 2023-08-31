#ifndef __LINKER_TOOLS_H__
#define __LINKER_TOOLS_H__

#define LINKER_SYMBOL8(sym)  extern uint8_t sym[]
#define LINKER_SYMBOL16(sym) extern uint16_t sym[]
#define LINKER_SYMBOL32(sym) extern uint32_t sym[]

#define INIT_FUNC(level)     __attribute__((__section__(".init_func." #level)))

#endif  // __LINKER_TOOLS_H__
