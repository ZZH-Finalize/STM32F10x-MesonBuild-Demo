#include "stm32f10x.h"
#include "arm_isr_attr.h"
#include "tiny_console/tiny_console.h"

#include "hal/usart/usart.h"

extern console_t* console;
extern volatile uint8_t rcv_flag;
extern usart_dev_t console_usart;

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(console_usart.reg, USART_IT_RXNE)) {
        USART_ClearITPendingBit(console_usart.reg, USART_IT_RXNE);
        console_input_char(console, (char) USART_ReceiveData(console_usart.reg));
        rcv_flag = 1;
    }

    // asm volatile('')
}
