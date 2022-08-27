#ifndef __SAMPLE_TIMER_H
#define __SAMPLE_TIMER_H

#include "stm32f10x.h"

#define SAMPLE_TIM              TIM2
#define SAMPLE_TIM_IRQn         TIM2_IRQn
#define SAMPLE_TIM_RCC          RCC_APB1Periph_TIM2
#define SAMPLE_TIM_IRQHandler   TIM2_IRQHandler


void Sample_Timer_Init(void);

#endif
