/*
@file: usart.c
@author: ZZH
@date: 2024-05-06
@info:
*/

#include "usart.h"
#include <stdint.h>
#include "hal/clock/clock.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "hal/dma/channel_mapping.h"

int usart_init(usart_dev_t* dev, USART_TypeDef* reg, USART_InitTypeDef* param)
{
    CHECK_PTR(dev, -EINVAL);
    CHECK_PTR(reg, -EINVAL);

    USART_InitTypeDef _param = {
        .USART_BaudRate = 115200,
        .USART_Mode = USART_Mode_Tx | USART_Mode_Rx,
        .USART_Parity = USART_Parity_No,
        .USART_StopBits = USART_StopBits_1,
        .USART_WordLength = USART_WordLength_8b,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
    };

    if (NULL == param)
        param = &_param;

    dev->reg = reg;

    int ret = clock_enable_for(reg);
    RETURN_IF_NZERO(ret, ret);

    USART_DeInit(reg);
    USART_Init(reg, param);
    USART_Cmd(reg, ENABLE);

    // setup gpio
    uint32_t reg_addr = (uint32_t) reg;
    GPIO_InitTypeDef aaa = {.GPIO_Speed = GPIO_Speed_50MHz};
    GPIO_TypeDef* gpiox = NULL;
    uint16_t tx_pin = 0, rx_pin = 0, cts_pin = 0, rts_pin = 0;

    switch (reg_addr) {
        case USART1_BASE:
            gpiox = GPIOA;
            tx_pin = GPIO_Pin_9;
            rx_pin = GPIO_Pin_10;
            cts_pin = GPIO_Pin_11;
            rts_pin = GPIO_Pin_12;
            break;

        case USART2_BASE:
            gpiox = GPIOA;
            tx_pin = GPIO_Pin_2;
            rx_pin = GPIO_Pin_3;
            cts_pin = GPIO_Pin_0;
            rts_pin = GPIO_Pin_1;
            break;

        case USART3_BASE:
            gpiox = GPIOB;
            tx_pin = GPIO_Pin_10;
            rx_pin = GPIO_Pin_11;
            cts_pin = GPIO_Pin_13;
            rts_pin = GPIO_Pin_14;
            break;

        case UART4_BASE:
            // todo: add UART4 gpio param
            break;

        case UART5_BASE:
            // todo: add UART5 gpio param
            break;

        default: break;
    }

    ret = clock_enable_for(gpiox);
    RETURN_IF_NZERO(ret, ret);

    if (param->USART_Mode & USART_Mode_Tx) {
        aaa.GPIO_Pin = tx_pin;
        aaa.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(gpiox, &aaa);
    }

    if (param->USART_Mode & USART_Mode_Rx) {
        aaa.GPIO_Pin = rx_pin;
        aaa.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(gpiox, &aaa);
    }

    if (param->USART_HardwareFlowControl & USART_HardwareFlowControl_RTS) {
        aaa.GPIO_Pin = rts_pin;
        aaa.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(gpiox, &aaa);
    }

    if (param->USART_HardwareFlowControl & USART_HardwareFlowControl_CTS) {
        aaa.GPIO_Pin = cts_pin;
        aaa.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(gpiox, &aaa);
    }

    return 0;
}
