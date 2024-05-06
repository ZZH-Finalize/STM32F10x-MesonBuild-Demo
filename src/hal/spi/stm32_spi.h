#ifndef __STM32_SPI_H__
#define __STM32_SPI_H__

#include "stm32f10x_spi.h"

static inline uint16_t spi_rw(SPI_TypeDef* pspi, uint16_t value)
{
    SPI_I2S_SendData(pspi, value);
    while (RESET == SPI_I2S_GetFlagStatus(pspi, SPI_I2S_FLAG_RXNE))
        __asm volatile ("nop");
    SPI_I2S_ClearFlag(pspi, SPI_I2S_FLAG_RXNE);

    return SPI_I2S_ReceiveData(pspi);
}


#endif // __STM32_SPI_H__
