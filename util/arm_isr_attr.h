#ifndef __ARM_ISR_ATTR_H__
#define __ARM_ISR_ATTR_H__

#include "gnu_attributes.h"

#define ARM_INTERRUPT(type) GNU_INTERRUPT(type)
#define ARM_IRQ             ARM_INTERRUPT(IRQ)
#define ARM_FIQ             ARM_INTERRUPT(FIQ)
#define ARM_SWI             ARM_INTERRUPT(SWI)
#define ARM_ABORT           ARM_INTERRUPT(ABORT)
#define ARM_UNDEF           ARM_INTERRUPT(UNDEF)

#endif // __ARM_ISR_ATTR_H__
