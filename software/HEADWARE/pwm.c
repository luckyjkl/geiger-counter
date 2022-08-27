#include "pwm.h"
//#include "led.h"
//PWM输出初始化
//arr:自动重装值
//psc:时钟预分频值
void TIM1_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	     
	RCC_APB2PeriphClockCmd(PWM_GPIO_RCC, ENABLE);      		//使能GPIOB时钟
    RCC_APB2PeriphClockCmd(PWM_TIM_RCC, ENABLE);       		//使能TIM1时钟
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE);		//TIM1引脚重定向

    //设置该引脚为复用输出功能，输出TIM1 CH3的PWM输出波形
    GPIO_InitStructure.GPIO_Pin = PWM_Pin;               	//TIM_CH3N
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PWM_GPIO, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = arr;                 		//自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = psc;              		//预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;            		//设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
    TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStructure);         		//初始化TIMx

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;       		//脉宽调制模式2
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	//互补端比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;                      		//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC3Init(PWM_TIM, &TIM_OCInitStructure);                		//初始化外设TIMx
	
	TIM_OC3PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);       		//CH3预装载使能
	
//	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
//	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
//	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
//	TIM_BDTRInitStructure.TIM_DeadTime = 0;  //这里调整死区大小0-0xff
//	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
//	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
//	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
//	TIM_BDTRConfig(PWM_TIM, &TIM_BDTRInitStructure);
	
	TIM_CtrlPWMOutputs(PWM_TIM, ENABLE);                       //MOE主输出使能

    TIM_ARRPreloadConfig(PWM_TIM, ENABLE);                     //使能TIMx在ARR上的预装载寄存器

    TIM_Cmd(PWM_TIM, ENABLE);                                  //使能TIM1
}
