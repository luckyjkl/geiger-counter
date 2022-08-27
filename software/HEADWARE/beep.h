#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

#define BEEP_GPIO		GPIOA
#define BEEP_RCC		RCC_APB2Periph_GPIOA
#define BEEP_Pin		GPIO_Pin_2

#define BEEP_ON			GPIO_SetBits(BEEP_GPIO, BEEP_Pin);
#define BEEP_OFF		GPIO_ResetBits(BEEP_GPIO, BEEP_Pin);

void BEEP_Init(void);

#endif
