/*
@file: usart.c
@author: ZZH
@date: 2024-05-06
@info:
*/

#include "usart.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "hal/dma/channel_mapping.h"

// clang-format off
const usart_dev_t usart[] = {
    {
        .reg = USART1,
        .irqn = USART1_IRQn,
        .gpio = {
            .base = GPIOA,
            .tx_pin = 9,
            .rx_pin = 10,
        },
        .dma = {
            .base = DMA1,
            .tx_channel = USART1_TX_DMA_CHAN,
            .rx_channel = USART1_RX_DMA_CHAN,
        },
    },
    {
        .reg = USART2,
        .irqn = USART2_IRQn,
        .gpio = {
            .base = GPIOA,
            .tx_pin = 2,
            .rx_pin = 3,
        },
        .dma = {
            .base = DMA1,
            .tx_channel = USART2_TX_DMA_CHAN,
            .rx_channel = USART2_RX_DMA_CHAN,
        },
    },
    {
        .reg = USART3,
        .irqn = USART3_IRQn,
        .gpio = {
            .base = GPIOB,
            .tx_pin = 10,
            .rx_pin = 11,
        },
        .dma = {
            .base = DMA1,
            .tx_channel = USART3_TX_DMA_CHAN,
            .rx_channel = USART3_RX_DMA_CHAN,
        },
    },
#ifdef STM32F10X_HD
    {
        .reg = UART4,
        .irqn = UART4_IRQn,
    },
    {
        .reg = UART5,
        .irqn = UART5_IRQn,
    },
#endif
};
// clang-format on
