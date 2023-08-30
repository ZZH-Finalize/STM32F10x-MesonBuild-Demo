#include <stdint.h>
#include "util/linker_tools.h"
#include "util/gnu_attributes.h"
#include "util/value_ops.h"

#include "system_stm32f10x.h"
extern int main(void);

#define ISR_VEC GNU_SECTION(.isr_vector)
#define HANDLER_ALIAS(name) __attribute__((__alias__(#name), __weak__))
#define NULL_HANDLER(name) void name(void) HANDLER_ALIAS(Null_Handler)
#define LOOP_HANDLER(name) void name(void) HANDLER_ALIAS(Default_Handler)


LINKER_SYMBOL32(__stack);
LINKER_SYMBOL32(__sbss);
LINKER_SYMBOL32(__ebss);
LINKER_SYMBOL32(__load_start);
LINKER_SYMBOL32(__load_end);
LINKER_SYMBOL32(__load_addr);

GNU_WEAK void Default_Handler(void)
{
    while (1)
    {
        *(uint32_t*) 0xE000ED0C = 0x5FA0005;
    }
}

GNU_WEAK void Null_Handler(void)
{
    
}

GNU_WEAK void Reset_Handler(void)
{
    volatile uint32_t* load_to = __load_start;
    volatile uint32_t* load_from = __load_addr;
    uint32_t load_size = ((uint32_t) __load_end - (uint32_t) __load_start) / 4;

    if (load_from != load_to)
    {
        for (uint32_t i = 0; i < load_size; i++)
        {
            *load_to = *load_from;
            load_to++;
            load_from++;
        }
    }

    volatile uint32_t* sbss = __sbss;
    volatile uint32_t* ebss = __ebss;

    for (; sbss < ebss; sbss++)
        *sbss = 0;

    SystemInit();
    main();
    Default_Handler();
}

NULL_HANDLER(NMI_Handler);
LOOP_HANDLER(HardFault_Handler);
LOOP_HANDLER(MemManage_Handler);
LOOP_HANDLER(BusFault_Handler);
LOOP_HANDLER(UsageFault_Handler);

NULL_HANDLER(SVC_Handler);
NULL_HANDLER(DebugMon_Handler);
NULL_HANDLER(PendSV_Handler);
NULL_HANDLER(SysTick_Handler);
NULL_HANDLER(WWDG_IRQHandler);
NULL_HANDLER(PVD_IRQHandler);
NULL_HANDLER(TAMPER_IRQHandler);
NULL_HANDLER(RTC_IRQHandler);
NULL_HANDLER(FLASH_IRQHandler);
NULL_HANDLER(RCC_IRQHandler);
NULL_HANDLER(EXTI0_IRQHandler);
NULL_HANDLER(EXTI1_IRQHandler);
NULL_HANDLER(EXTI2_IRQHandler);
NULL_HANDLER(EXTI3_IRQHandler);
NULL_HANDLER(EXTI4_IRQHandler);
NULL_HANDLER(DMA1_Channel1_IRQHandler);
NULL_HANDLER(DMA1_Channel2_IRQHandler);
NULL_HANDLER(DMA1_Channel3_IRQHandler);
NULL_HANDLER(DMA1_Channel4_IRQHandler);
NULL_HANDLER(DMA1_Channel5_IRQHandler);
NULL_HANDLER(DMA1_Channel6_IRQHandler);
NULL_HANDLER(DMA1_Channel7_IRQHandler);
NULL_HANDLER(ADC1_2_IRQHandler);
NULL_HANDLER(USB_HP_CAN1_TX_IRQHandler);
NULL_HANDLER(USB_LP_CAN1_RX0_IRQHandler);
NULL_HANDLER(CAN1_RX1_IRQHandler);
NULL_HANDLER(CAN1_SCE_IRQHandler);
NULL_HANDLER(EXTI9_5_IRQHandler);
NULL_HANDLER(TIM1_BRK_IRQHandler);
NULL_HANDLER(TIM1_UP_IRQHandler);
NULL_HANDLER(TIM1_TRG_COM_IRQHandler);
NULL_HANDLER(TIM1_CC_IRQHandler);
NULL_HANDLER(TIM2_IRQHandler);
NULL_HANDLER(TIM3_IRQHandler);
NULL_HANDLER(TIM4_IRQHandler);
NULL_HANDLER(I2C1_EV_IRQHandler);
NULL_HANDLER(I2C1_ER_IRQHandler);
NULL_HANDLER(I2C2_EV_IRQHandler);
NULL_HANDLER(I2C2_ER_IRQHandler);
NULL_HANDLER(SPI1_IRQHandler);
NULL_HANDLER(SPI2_IRQHandler);
NULL_HANDLER(USART1_IRQHandler);
NULL_HANDLER(USART2_IRQHandler);
NULL_HANDLER(USART3_IRQHandler);
NULL_HANDLER(EXTI15_10_IRQHandler);
NULL_HANDLER(RTCAlarm_IRQHandler);
NULL_HANDLER(USBWakeUp_IRQHandler);

#define BootRAM 0xF108F85F

ISR_VEC volatile uint32_t isr_vectors[] = {
    (uint32_t) __stack,
    (uint32_t) Reset_Handler,
    (uint32_t) NMI_Handler,
    (uint32_t) HardFault_Handler,
    (uint32_t) MemManage_Handler,
    (uint32_t) BusFault_Handler,
    (uint32_t) UsageFault_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) SVC_Handler,
    (uint32_t) DebugMon_Handler,
    (uint32_t) 0,
    (uint32_t) PendSV_Handler,
    (uint32_t) SysTick_Handler,
    (uint32_t) WWDG_IRQHandler,
    (uint32_t) PVD_IRQHandler,
    (uint32_t) TAMPER_IRQHandler,
    (uint32_t) RTC_IRQHandler,
    (uint32_t) FLASH_IRQHandler,
    (uint32_t) RCC_IRQHandler,
    (uint32_t) EXTI0_IRQHandler,
    (uint32_t) EXTI1_IRQHandler,
    (uint32_t) EXTI2_IRQHandler,
    (uint32_t) EXTI3_IRQHandler,
    (uint32_t) EXTI4_IRQHandler,
    (uint32_t) DMA1_Channel1_IRQHandler,
    (uint32_t) DMA1_Channel2_IRQHandler,
    (uint32_t) DMA1_Channel3_IRQHandler,
    (uint32_t) DMA1_Channel4_IRQHandler,
    (uint32_t) DMA1_Channel5_IRQHandler,
    (uint32_t) DMA1_Channel6_IRQHandler,
    (uint32_t) DMA1_Channel7_IRQHandler,
    (uint32_t) ADC1_2_IRQHandler,
    (uint32_t) USB_HP_CAN1_TX_IRQHandler,
    (uint32_t) USB_LP_CAN1_RX0_IRQHandler,
    (uint32_t) CAN1_RX1_IRQHandler,
    (uint32_t) CAN1_SCE_IRQHandler,
    (uint32_t) EXTI9_5_IRQHandler,
    (uint32_t) TIM1_BRK_IRQHandler,
    (uint32_t) TIM1_UP_IRQHandler,
    (uint32_t) TIM1_TRG_COM_IRQHandler,
    (uint32_t) TIM1_CC_IRQHandler,
    (uint32_t) TIM2_IRQHandler,
    (uint32_t) TIM3_IRQHandler,
    (uint32_t) TIM4_IRQHandler,
    (uint32_t) I2C1_EV_IRQHandler,
    (uint32_t) I2C1_ER_IRQHandler,
    (uint32_t) I2C2_EV_IRQHandler,
    (uint32_t) I2C2_ER_IRQHandler,
    (uint32_t) SPI1_IRQHandler,
    (uint32_t) SPI2_IRQHandler,
    (uint32_t) USART1_IRQHandler,
    (uint32_t) USART2_IRQHandler,
    (uint32_t) USART3_IRQHandler,
    (uint32_t) EXTI15_10_IRQHandler,
    (uint32_t) RTCAlarm_IRQHandler,
    (uint32_t) USBWakeUp_IRQHandler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) BootRAM,
};

const uint32_t isr_vector_size = ARRAY_SIZE(isr_vectors);

/*
.word	_estack
.word	Reset_Handler
.word	NMI_Handler
.word	HardFault_Handler
.word	MemManage_Handler
.word	BusFault_Handler
.word	UsageFault_Handler
.word	0
.word	0
.word	0
.word	0
.word	SVC_Handler
.word	DebugMon_Handler
.word	0
.word	PendSV_Handler
.word	SysTick_Handler
.word	WWDG_IRQHandler
.word	PVD_IRQHandler
.word	TAMPER_IRQHandler
.word	RTC_IRQHandler
.word	FLASH_IRQHandler
.word	RCC_IRQHandler
.word	EXTI0_IRQHandler
.word	EXTI1_IRQHandler
.word	EXTI2_IRQHandler
.word	EXTI3_IRQHandler
.word	EXTI4_IRQHandler
.word	DMA1_Channel1_IRQHandler
.word	DMA1_Channel2_IRQHandler
.word	DMA1_Channel3_IRQHandler
.word	DMA1_Channel4_IRQHandler
.word	DMA1_Channel5_IRQHandler
.word	DMA1_Channel6_IRQHandler
.word	DMA1_Channel7_IRQHandler
.word	ADC1_2_IRQHandler
.word	USB_HP_CAN1_TX_IRQHandler
.word	USB_LP_CAN1_RX0_IRQHandler
.word	CAN1_RX1_IRQHandler
.word	CAN1_SCE_IRQHandler
.word	EXTI9_5_IRQHandler
.word	TIM1_BRK_IRQHandler
.word	TIM1_UP_IRQHandler
.word	TIM1_TRG_COM_IRQHandler
.word	TIM1_CC_IRQHandler
.word	TIM2_IRQHandler
.word	TIM3_IRQHandler
.word	TIM4_IRQHandler
.word	I2C1_EV_IRQHandler
.word	I2C1_ER_IRQHandler
.word	I2C2_EV_IRQHandler
.word	I2C2_ER_IRQHandler
.word	SPI1_IRQHandler
.word	SPI2_IRQHandler
.word	USART1_IRQHandler
.word	USART2_IRQHandler
.word	USART3_IRQHandler
.word	EXTI15_10_IRQHandler
.word	RTCAlarm_IRQHandler
.word	USBWakeUp_IRQHandler
.word	0
.word	0
.word	0
.word	0
.word	0
.word	0
.word	0
.word	BootRAM      //@0x108. This is for boot in RAM mode for STM32F10x Medium Density devices.
*/
