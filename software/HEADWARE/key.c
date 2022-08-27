#include "delay.h"
#include "key.h"

//按键初始化函数
//PA15和PC5设置成输入
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//使能PORTA,PORTC时钟
	RCC_APB2PeriphClockCmd(KEY2_RCC | KEY3_RCC, ENABLE);
	//关闭JATG,使能SWD，可以用SWD模式调试
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	GPIO_InitStructure.GPIO_Pin = KEY2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//设置成上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY2_GPIO, &GPIO_InitStructure);			//初始化GPIOA15

	GPIO_InitStructure.GPIO_Pin = KEY3_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//设置成下拉输入
	GPIO_Init(KEY3_GPIO, &GPIO_InitStructure);			//初始化GPIOC5
}
//按键处理函数
//mode:0,不支持连续按；1，支持连续按
//return:0,没有任何按键
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1;			//按键松开标志
	if(mode)
		key_up = 1;					//支持连按
	if(key_up && (KEY2 == 0 || KEY3 == 1))
	{
		delay_ms(30);		//延时去抖动
		key_up = 0;
		if(KEY2 == 0)
			return KEY2_PRES;
		if(KEY3 == 1)
			return KEY3_PRES;
	}
	else if(KEY2 == 1 && KEY3 == 0)
		key_up = 1;
	return 0;
}
