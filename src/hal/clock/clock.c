/*
@file: clock.c
@author: ZZH
@date: 2024-05-06
@info:
*/

#include "clock.h"
#include "stm32f10x_rcc.h"

#define __CLOCK_HANDLER(per, bus, en)                           \
    case per##_BASE:                                            \
        RCC_##bus##PeriphClockCmd(RCC_##bus##Periph_##per, en); \
        break

int clock_cmd_for(void* reg, FunctionalState cmd)
{
    unsigned int __reg = (unsigned int) reg;
    switch (__reg) {
        __CLOCK_HANDLER(DMA1, AHB, cmd);
        __CLOCK_HANDLER(DMA2, AHB, cmd);

        __CLOCK_HANDLER(USART1, APB2, cmd);
        __CLOCK_HANDLER(USART2, APB1, cmd);
        __CLOCK_HANDLER(USART3, APB1, cmd);
        __CLOCK_HANDLER(UART4, APB1, cmd);
        __CLOCK_HANDLER(UART5, APB1, cmd);

        __CLOCK_HANDLER(GPIOA, APB2, cmd);
        __CLOCK_HANDLER(GPIOB, APB2, cmd);
        __CLOCK_HANDLER(GPIOC, APB2, cmd);
        __CLOCK_HANDLER(GPIOD, APB2, cmd);
        __CLOCK_HANDLER(GPIOE, APB2, cmd);
        __CLOCK_HANDLER(GPIOF, APB2, cmd);
        __CLOCK_HANDLER(GPIOG, APB2, cmd);

        __CLOCK_HANDLER(ADC1, APB2, cmd);
        __CLOCK_HANDLER(ADC2, APB2, cmd);
        __CLOCK_HANDLER(ADC3, APB2, cmd);

        __CLOCK_HANDLER(TIM1, APB2, cmd);
        __CLOCK_HANDLER(TIM2, APB1, cmd);
        __CLOCK_HANDLER(TIM3, APB1, cmd);
        __CLOCK_HANDLER(TIM4, APB1, cmd);
        __CLOCK_HANDLER(TIM5, APB1, cmd);
        __CLOCK_HANDLER(TIM6, APB1, cmd);
        __CLOCK_HANDLER(TIM7, APB1, cmd);
        __CLOCK_HANDLER(TIM8, APB2, cmd);
        __CLOCK_HANDLER(TIM9, APB2, cmd);
        __CLOCK_HANDLER(TIM10, APB2, cmd);
        __CLOCK_HANDLER(TIM11, APB2, cmd);
        __CLOCK_HANDLER(TIM12, APB1, cmd);
        __CLOCK_HANDLER(TIM13, APB1, cmd);
        __CLOCK_HANDLER(TIM14, APB1, cmd);
        __CLOCK_HANDLER(TIM15, APB2, cmd);
        __CLOCK_HANDLER(TIM16, APB2, cmd);
        __CLOCK_HANDLER(TIM17, APB2, cmd);

        __CLOCK_HANDLER(SPI1, APB2, cmd);
        __CLOCK_HANDLER(SPI2, APB1, cmd);
        __CLOCK_HANDLER(SPI3, APB1, cmd);

        __CLOCK_HANDLER(I2C1, APB1, cmd);
        __CLOCK_HANDLER(I2C2, APB1, cmd);

        __CLOCK_HANDLER(CAN1, APB1, cmd);
        __CLOCK_HANDLER(CAN2, APB1, cmd);

        // __CLOCK_HANDLER(SRAM, AHB, cmd);
        __CLOCK_HANDLER(CRC, AHB, cmd);
        // __CLOCK_HANDLER(FSMC, AHB, cmd);
        __CLOCK_HANDLER(SDIO, AHB, cmd);
        __CLOCK_HANDLER(AFIO, APB2, cmd);
        __CLOCK_HANDLER(WWDG, APB1, cmd);
        // __CLOCK_HANDLER(USB, APB1, cmd);
        __CLOCK_HANDLER(BKP, APB1, cmd);
        __CLOCK_HANDLER(PWR, APB1, cmd);
        __CLOCK_HANDLER(DAC, APB1, cmd);
        __CLOCK_HANDLER(CEC, APB1, cmd);

        default: return -EINVAL;
    }

    return 0;
}
