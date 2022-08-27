#ifndef __EXTI_H
#define __EXTI_H

#include "stm32f10x.h"

#define EXTI_GPIO				GPIOA
#define EXTI_RCC				RCC_APB2Periph_GPIOA
#define EXTI_PortSourceGPIO		GPIO_PortSourceGPIOA
#define EXTI_GPIO_PinSource 	GPIO_PinSource1
#define EXTI_GPIO_Pin			GPIO_Pin_1
#define EXTI_COUNT_Line			EXTI_Line1
#define EXTI_COUNT_IRQn			EXTI1_IRQn
#define EXTI_COUNT_IRQHandler	EXTI1_IRQHandler

void EXTIX_Init(void);

#endif
