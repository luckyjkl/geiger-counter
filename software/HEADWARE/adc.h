#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

#define Battery_ADC         ADC1
#define Battery_ADC_GPIO    GPIOA
#define Battery_ADC_Pin     GPIO_Pin_3
#define Battery_ADC_RCC     RCC_APB2Periph_ADC1
#define Battery_GPIO_RCC    RCC_APB2Periph_GPIOA
#define Battery_ADC_Channel ADC_Channel_3


void Battery_ADC_Init(void);
u16 Get_adc(u8 ch);
float Get_Battery_Voltage(void);
void OLED_Show_Voltage(void);

#endif
