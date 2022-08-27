#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"

#define SPIx_GPIO	GPIOB
#define SPIx_RCC	RCC_APB2Periph_GPIOB
#define SPIx		SPI2
#define SPIX_RCC	RCC_APB1Periph_SPI2
#define SPIx_SCK	GPIO_Pin_13
#define SPIx_MISO	GPIO_Pin_14
#define SPIx_MOSI	GPIO_Pin_15

void SPIx_Init(void);
void SPIx_SetSpeed(u8 SpeedSet);
u8 SPIx_ReadWriteByte(u8 TxData);

#endif
