#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED0_GPIO	GPIOE
#define LED0_RCC	RCC_APB2Periph_GPIOE
#define LED0		GPIO_Pin_5

#define LED1_GPIO	GPIOE
#define LED1_RCC	RCC_APB2Periph_GPIOE
#define LED1		GPIO_Pin_6

#define LED0_ON		GPIO_ResetBits(LED0_GPIO, LED0)
#define LED0_OFF	GPIO_SetBits(LED0_GPIO, LED0)

#define LED1_ON		GPIO_ResetBits(LED1_GPIO, LED1)
#define LED1_OFF	GPIO_SetBits(LED1_GPIO, LED1)

void LED_Init(void);			//LED初始化函数

#endif
