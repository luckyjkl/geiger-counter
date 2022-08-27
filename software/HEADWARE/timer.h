#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

#define MAX_QUEUE_LENGTH 600       // 队列长度

void TIM3_Init(u16 arr, u16 psc);
void Show_Radiation_Dose(void);

#endif
