
/*
@file: usart.h
@author: ZZH
@date: 2024-05-06
@info:
*/

#ifndef __USART_H__
#define __USART_H__

#include <errno.h>
#include <stdint.h>
#include "arg_checkers.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "hal/clock/clock.h"

typedef struct
{
    USART_TypeDef* reg;
    IRQn_Type irqn;

    struct
    {
        DMA_TypeDef* base;
        DMA_Channel_TypeDef *tx_channel, *rx_channel;
    } dma;

} usart_dev_t;

static inline int usart_cmd(usart_dev_t* dev, FunctionalState new_state)
{
    CHECK_PTR(dev, -EINVAL);
    CHECK_PTR(dev->reg, -EINVAL);

    USART_Cmd(dev->reg, new_state);

    return 0;
}

int usart_init(usart_dev_t* dev, USART_TypeDef* reg, USART_InitTypeDef* param);

#endif // __USART_H__
