#include "stm32f10x.h"

void USART1_IRQHandler(void)
{
    static uint8_t flag = 0;

    if (USART_GetITStatus(USART1, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        // USART_ClearITPendingBit(USART1, USART_IT_TC);

        (void) USART1->DR;

        if (flag)
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
        else
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);

        flag = !flag;
    }

    // asm volatile('')
}
