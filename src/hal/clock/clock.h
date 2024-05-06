/*
@file: clock.h
@author: ZZH
@date: 2024-05-06
@info:
*/

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <errno.h>
#include "stm32f10x.h"

int clock_cmd_for(void* reg, FunctionalState cmd);

static inline int clock_enable_for(void* reg)
{
    return clock_cmd_for(reg, ENABLE);
}

static inline int clock_disable_for(void* reg)
{
    return clock_cmd_for(reg, DISABLE);
}

#endif // __CLOCK_H__
