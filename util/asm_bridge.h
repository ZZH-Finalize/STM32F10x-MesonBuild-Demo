#ifndef __ASM_BRIDGE_H__
#define __ASM_BRIDGE_H__

#define ASM_READ_REG(reg, var)  asm volatile("mov %0, " reg : "=r"(var))
#define ASM_READ_XREG(reg, var) asm volatile("mrs %0, " reg : "=r"(var))

#endif // __ASM_BRIDGE_H__
