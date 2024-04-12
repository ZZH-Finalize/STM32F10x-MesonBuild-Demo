#ifndef __STACK_TRACE_H__
#define __STACK_TRACE_H__

#include "stm32f10x_usart.h"

// length of lines (6 words per line)
#define STACK_TRACE_LENGTH 16

void print_stack_trace(USART_TypeDef *usartx, uint32_t *stack);

#endif // __STACK_TRACE_H__
