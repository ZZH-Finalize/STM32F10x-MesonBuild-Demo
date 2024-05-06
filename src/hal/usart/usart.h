
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

    struct
    {
        GPIO_TypeDef* base;
        uint8_t tx_pin;
        uint8_t rx_pin;
    } gpio;

} usart_dev_t;

static inline int usart_init(usart_dev_t* dev, USART_TypeDef* reg,
                             USART_InitTypeDef* param)
{
    CHECK_PTR(dev, -EINVAL);
    CHECK_PTR(reg, -EINVAL);
    CHECK_PTR(param, -EINVAL);

    dev->reg = reg;

    USART_DeInit(reg);
    USART_Init(reg, param);

    return 0;
}

static inline int usart_cmd(usart_dev_t* dev, FunctionalState new_state)
{
    CHECK_PTR(dev, -EINVAL);
    CHECK_PTR(dev->reg, -EINVAL);

    USART_Cmd(dev->reg, new_state);

    return 0;
}

static inline int usart_def_init(usart_dev_t* dev, USART_TypeDef* reg)
{
    CHECK_PTR(dev, -EINVAL);
    CHECK_PTR(reg, -EINVAL);

    USART_InitTypeDef param = {
        .USART_BaudRate = 115200,
        .USART_Mode = USART_Mode_Tx | USART_Mode_Rx,
        .USART_Parity = USART_Parity_No,
        .USART_StopBits = USART_StopBits_1,
        .USART_WordLength = USART_WordLength_8b,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
    };

    int ret = clock_enable_for(reg);
    RETURN_IF_NZERO(ret, ret);

    ret = usart_init(dev, reg, &param);
    RETURN_IF_NZERO(ret, ret);

    // setup gpio

    return 0;
}

const usart_dev_t usart[];

#endif // __USART_H__
