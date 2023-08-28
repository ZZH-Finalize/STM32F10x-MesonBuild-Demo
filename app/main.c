#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#include "delay.h"


void clock_init(void)
{
    RCC_DeInit();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

void gpio_init(void)
{
    GPIO_InitTypeDef init_param = {
        .GPIO_Speed = GPIO_Speed_50MHz
    };

    GPIO_DeInit(GPIOA);

    // 复用推挽
    init_param.GPIO_Mode = GPIO_Mode_AF_PP;

    // USART1 - TXD
    init_param.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &init_param);

    // 浮空输入
    init_param.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    // USART1 - RXD
    init_param.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &init_param);
}

void usart_init(void)
{
    USART_InitTypeDef init_param = {
        .USART_BaudRate = 115200,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        .USART_Mode = USART_Mode_Tx | USART_Mode_Rx,
        .USART_Parity = USART_Parity_No,
        .USART_StopBits = USART_StopBits_1,
        .USART_WordLength = USART_WordLength_8b
    };

    USART_Init(USART1, &init_param);
    USART_Cmd(USART1, ENABLE);
}

void nvic_init()
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);

    NVIC_InitTypeDef init_param = {
        .NVIC_IRQChannel = USART1_IRQn,
        .NVIC_IRQChannelCmd = ENABLE,
        .NVIC_IRQChannelPreemptionPriority = 12,
        .NVIC_IRQChannelSubPriority = 14
    };

    NVIC_Init(&init_param);
    // USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

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

int main()
{
    const char msg[] = { "Hello World!\r\n" };

    clock_init();
    gpio_init();
    usart_init();
    nvic_init();

    while (1)
    {
        for (uint32_t i = 0; i < sizeof(msg)-1; i++)
        {
            USART_SendData(USART1, msg[i]);
            while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TC));
            USART_ClearFlag(USART1, USART_FLAG_TC);
        }

        // for delay
        delay_ms_sw(100);
    }

    return 0;
}
