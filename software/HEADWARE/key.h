#ifndef __KEY_H__
#define __KEY_H__

//#include "sys.h"
#include "stm32f10x.h"

#define KEY2_GPIO 	GPIOE
#define KEY2_RCC	RCC_APB2Periph_GPIOE
#define KEY2_Pin	GPIO_Pin_4

#define KEY3_GPIO 	GPIOA
#define KEY3_RCC	RCC_APB2Periph_GPIOA
#define KEY3_Pin	GPIO_Pin_0

#define KEY2 GPIO_ReadInputDataBit(KEY2_GPIO, KEY2_Pin) 
#define KEY3 GPIO_ReadInputDataBit(KEY3_GPIO, KEY3_Pin)   

#define KEY2_PRES 1         //KEY2
#define KEY3_PRES 2         //KEY3
//#define WKUP_PRES 3         //WK_UP

void KEY_Init(void);        //按键初始化
u8 KEY_Scan(u8 mode);       //按键扫描

#endif
