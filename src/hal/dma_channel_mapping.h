#ifndef __DMA_CHANNEL_MAPPING_H__
#define __DMA_CHANNEL_MAPPING_H__

#include "stm32f10x_dma.h"

// dma1 channel1
#define ADC1_DMA_CHAN      DMA1_Channel1
#define TIM2_CH3_DMA_CHAN  DMA1_Channel1
#define TIM4_CH1_DMA_CHAN  DMA1_Channel1

// dma1 channel2
#define SPI1_RX_DMA_CHAN   DMA1_Channel2
#define USART3_TX_DMA_CHAN DMA1_Channel2
#define TIM1_CH1_DMA_CHAN  DMA1_Channel2
#define TIM2_UP_DMA_CHAN   DMA1_Channel2
#define TIM3_CH3_DMA_CHAN  DMA1_Channel2

// dma1 channel3
#define SPI1_TX_DMA_CHAN   DMA1_Channel3
#define USART3_RX_DMA_CHAN DMA1_Channel3
#define TIM1_CH2_DMA_CHAN  DMA1_Channel3
#define TIM3_CH4_DMA_CHAN  DMA1_Channel3
#define TIM3_UP_DMA_CHAN   DMA1_Channel3

// dma1 channel4
#define SPI2_RX_DMA_CHAN   DMA1_Channel4
#define I2S2_RX_DMA_CHAN   DMA1_Channel4
#define USART1_TX_DMA_CHAN DMA1_Channel4
#define I2C2_TX_DMA_CHAN   DMA1_Channel4
#define TIM1_TX4_DMA_CHAN  DMA1_Channel4
#define TIM1_TRIG_DMA_CHAN DMA1_Channel4
#define TIM1_COM_DMA_CHAN  DMA1_Channel4
#define TIM4_CH2_DMA_CHAN  DMA1_Channel4

// dma1 channel5
#define SPI2_TX_DMA_CHAN   DMA1_Channel5
#define I2S2_TX_DMA_CHAN   DMA1_Channel5
#define USART1_RX_DMA_CHAN DMA1_Channel5
#define I2C2_RX_DMA_CHAN   DMA1_Channel5
#define TIM1_UP_DMA_CHAN   DMA1_Channel5
#define TIM2_CH1_DMA_CHAN  DMA1_Channel5
#define TIM4_CH3_DMA_CHAN  DMA1_Channel5

// dma1 channel6
#define USART2_RX_DMA_CHAN DMA1_Channel6
#define I2C1_TX_DMA_CHAN   DMA1_Channel6
#define TIM1_CH3_DMA_CHAN  DMA1_Channel6
#define TIM3_CH1_DMA_CHAN  DMA1_Channel6
#define TIM3_TRIG_DMA_CHAN DMA1_Channel6

// dma1 channel7
#define USART2_TX_DMA_CHAN DMA1_Channel7
#define I2C1_RX_DMA_CHAN   DMA1_Channel7
#define TIM2_CH2_DMA_CHAN  DMA1_Channel7
#define TIM2_CH4_DMA_CHAN  DMA1_Channel7
#define TIM4_UP_DMA_CHAN   DMA1_Channel7

// dma2 channel1
#define SPI3_RX_DMA_CHAN   DMA2_Channel1
#define I2S3_RX_DMA_CHAN   DMA2_Channel1
#define TIM5_CH4_DMA_CHAN  DMA2_Channel1
#define TIM5_TRIG_DMA_CHAN DMA2_Channel1
#define TIM8_CH3_DMA_CHAN  DMA2_Channel1
#define TIM8_UP_DMA_CHAN   DMA2_Channel1

// dma2 channel2
#define SPI3_TX_DMA_CHAN   DMA2_Channel2
#define I2S3_TX_DMA_CHAN   DMA2_Channel2
#define TIM5_CH3_DMA_CHAN  DMA2_Channel2
#define TIM5_UP_DMA_CHAN   DMA2_Channel2
#define TIM8_CH4_DMA_CHAN  DMA2_Channel2
#define TIM8_TRIG_DMA_CHAN DMA2_Channel2
#define TIM8_COM_DMA_CHAN  DMA2_Channel2

// dma2 channel3
#define USART4_RX_DMA_CHAN DMA2_Channel3
#define TIM6_UP_DMA_CHAN   DMA2_Channel3
#define DAC_CH1_DMA_CHAN   DMA2_Channel3
#define TIM8_CH1_DMA_CHAN  DMA2_Channel3

// dma2 channel4
#define SDIO_DMA_CHAN      DMA2_Channel4
#define TIM5_CH2_DMA_CHAN  DMA2_Channel4
#define TIM7_UP_DMA_CHAN   DMA2_Channel4
#define DAC_CH2_DMA_CHAN   DMA2_Channel4

// dma2 channel5
#define ADC3_DMA_CHAN      DMA2_Channel5
#define USART4_TX_DMA_CHAN DMA2_Channel5
#define TIM5_CH1_DMA_CHAN  DMA2_Channel5
#define TIM8_CH2_DMA_CHAN  DMA2_Channel5

#endif // __DMA_CHANNEL_MAPPING_H__
