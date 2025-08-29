/*
@file: gpio.h
@author: ZZH
@date: 2024-05-07
@info:
*/

#ifndef __GPIO_H__
#define __GPIO_H__

#include <stddef.h>
#include <errno.h>
#include "arg_checkers.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

typedef struct
{
    GPIO_TypeDef* gpiox;
    u32 pin;
} gpio_dev_t;

static inline int gpio_init(gpio_dev_t* gpio, GPIOMode_TypeDef mode)
{
    CHECK_PTR(gpio, -EINVAL);
    CHECK_PTR(gpio->gpiox, -EINVAL);

    GPIO_InitTypeDef aaa = {
        .GPIO_Pin = gpio->pin,
        .GPIO_Mode = mode,
        .GPIO_Speed = GPIO_Speed_50MHz,
    };

    GPIO_Init(gpio->gpiox, &aaa);

    return 0;
}

static inline int gpio_write(gpio_dev_t* gpio, BitAction action)
{
    CHECK_PTR(gpio, -EINVAL);
    CHECK_PTR(gpio->gpiox, -EINVAL);

    GPIO_WriteBit(gpio->gpiox, gpio->pin, action);

    return 0;
}

static inline int gpio_read(gpio_dev_t* gpio, BitAction* action)
{
    CHECK_PTR(gpio, -EINVAL);
    CHECK_PTR(gpio->gpiox, -EINVAL);

    *action = GPIO_ReadInputDataBit(gpio->gpiox, gpio->pin);

    return 0;
}

#endif // __GPIO_H__
