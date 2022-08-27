#include "beep.h"

void BEEP_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(BEEP_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin 	= BEEP_Pin;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;			//推挽输出
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(BEEP_GPIO, &GPIO_InitStructure);
	BEEP_OFF;
}
