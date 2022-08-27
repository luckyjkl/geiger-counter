#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
//#include "key.h"

int Geiger_Count = 0;
int Last_Geiger_Count = 0;			//上次的计数值

//外部中断初始化函数
void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //外部中断，需要使能AFIO时钟
	RCC_APB2PeriphClockCmd(EXTI_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin 	= EXTI_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;			//上拉输入
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(EXTI_GPIO, &GPIO_InitStructure);

//    KEY_Init();         //初始化按键
    //GPIOA.1中断线及中断初始化配置
    GPIO_EXTILineConfig(EXTI_PortSourceGPIO, EXTI_GPIO_PinSource);

    EXTI_InitStructure.EXTI_Line = EXTI_COUNT_Line;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);         //初始化外部中断寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI_COUNT_IRQn;        //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);

}

void EXTI_COUNT_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_COUNT_Line) != RESET)          //检查EXTI更新中断是否发生
    {
        Geiger_Count++;
        EXTI_ClearITPendingBit(EXTI_COUNT_Line);
    }
//    Geiger_Count++;
//    EXTI_ClearITPendingBit(EXTI_COUNT_Line);
}

