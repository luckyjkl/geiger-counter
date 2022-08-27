#include "led.h"

//初始化PA8和PD2为输出口，并使能这两个口的时钟
//LED IO初始化
void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LED0_RCC | LED1_RCC, ENABLE); //使能PA,PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin = LED0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
	GPIO_Init(LED0_GPIO, &GPIO_InitStructure);				//初始化
	GPIO_SetBits(LED0_GPIO, LED0);					//输出高
	
	GPIO_InitStructure.GPIO_Pin = LED1;
	GPIO_Init(LED1_GPIO, &GPIO_InitStructure);			
	GPIO_SetBits(LED1_GPIO, LED1);	
}
