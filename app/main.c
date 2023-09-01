#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#include "delay.h"

#include "util/mem_mana/mem_mana.h"

void clockInit(void)
{
    RCC_DeInit();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

void gpioInit(void)
{
    GPIO_InitTypeDef init_param = {.GPIO_Speed = GPIO_Speed_50MHz};

    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOC);

    // 推挽输出
    init_param.GPIO_Mode = GPIO_Mode_Out_PP;

    // Led
    init_param.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOC, &init_param);

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

void usartInit(void)
{
    USART_InitTypeDef init_param = {
        .USART_BaudRate = 115200,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        .USART_Mode = USART_Mode_Tx | USART_Mode_Rx,
        .USART_Parity = USART_Parity_No,
        .USART_StopBits = USART_StopBits_1,
        .USART_WordLength = USART_WordLength_8b};

    USART_Init(USART1, &init_param);
    USART_Cmd(USART1, ENABLE);
}

void nvicInit()
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);

    NVIC_InitTypeDef init_param = {.NVIC_IRQChannel = USART1_IRQn,
                                   .NVIC_IRQChannelCmd = ENABLE,
                                   .NVIC_IRQChannelPreemptionPriority = 12,
                                   .NVIC_IRQChannelSubPriority = 14};

    NVIC_Init(&init_param);
    // USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

int main()
{
    const char msg[] = {"Hello World!\r\n"};

    clockInit();
    gpioInit();
    usartInit();
    nvicInit();

    void *pmem[5];
    pmem[0] = memAlloc(5, 0);
    pmem[1] = memAlloc(9, 0);
    pmem[2] = memAlloc(7, 0);
    pmem[3] = memAlloc(120, 0);
    memFree(pmem[2]);
    memFree(pmem[0]);
    memFree(pmem[3]);
    memFree(pmem[1]);

    while (1) {
        for (uint32_t i = 0; i < sizeof(msg) - 1; i++) {
            USART_SendData(USART1, msg[i]);
            while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TC))
                ;
            USART_ClearFlag(USART1, USART_FLAG_TC);
        }

        // for delay
        delay_ms_sw(100);
    }

    return 0;
}
