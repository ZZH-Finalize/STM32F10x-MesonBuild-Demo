#include <stdarg.h>
#include <stdio.h>
#include "prints.h"


void print_str(USART_TypeDef* usartx, const char* str)
{
    while('\0'!= *str)
        print_char(usartx, *str++);
}

void print_hex(USART_TypeDef* usartx, uint32_t num)
{
    for (int i = 0;i < 8;i++)
    {
        uint8_t val = (num & 0xF0000000) >> 28;

        if (val > 9)
            print_char(usartx, (val - 10) + 'A');
        else
            print_char(usartx, val + '0');

        num <<= 4;
    }
}

void print_dec(USART_TypeDef* usartx, uint32_t num)
{

}

int usart_printf(USART_TypeDef* usartx, const char* fmt, ...)
{

}
