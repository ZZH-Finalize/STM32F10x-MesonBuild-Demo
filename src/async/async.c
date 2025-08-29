#include "async.h"
#include "stm32f10x.h"

void trigger_svc()
{
    // SCB->SHP[2] |=
    asm volatile("cpsie f");
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}
