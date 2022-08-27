#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

#define PWM_GPIO		GPIOB
#define PWM_Pin			GPIO_Pin_1
#define PWM_TIM_RCC		RCC_APB2Periph_TIM1
#define PWM_GPIO_RCC	RCC_APB2Periph_GPIOB
#define PWM_TIM			TIM1

void TIM1_PWM_Init(u16 arr, u16 psc);

#endif
