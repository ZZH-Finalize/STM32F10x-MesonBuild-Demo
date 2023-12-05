#ifndef __PRINTS_H__
#define __PRINTS_H__

#include "stm32f10x_usart.h"
#include "util/gnu_attributes.h"

static inline void print_char(USART_TypeDef* usartx, char ch)
{
    // wait for last transmisson
    while (USART_SR_TC != (usartx->SR & USART_SR_TC)) asm volatile("nop");

    usartx->DR = ch;
}

void print_str(USART_TypeDef* usartx, const char* str);
void print_hex(USART_TypeDef* usartx, uint32_t num);
void print_dec(USART_TypeDef* usartx, uint32_t num);
// void print_double(USART_TypeDef* usartx, double num);
int usart_printf(USART_TypeDef* usartx, const char* fmt, ...) GNU_PRINTF(2, 3);

#endif // __PRINTS_H__
