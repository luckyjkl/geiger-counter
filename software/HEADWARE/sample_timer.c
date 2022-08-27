#include "sample_timer.h"
#include "usart.h"
#include "adc.h"
#include "kalman_filter.h"
//通用定时器2中断初始化
//这里时钟选择为APB1两倍，而APB1为36M
//arr:自动重装值
//psc:时钟预分频数
//使用的是定时器2


__IO float vol_kf;      // 卡尔曼滤波后的电压

void Sample_Timer_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(SAMPLE_TIM_RCC, ENABLE);        //时钟TIM3使能
    //定时器TIM3初始化
    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;               //设置自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;               //设置时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数
    TIM_TimeBaseInit(SAMPLE_TIM, &TIM_TimeBaseStructure);       //初始化TIM
    TIM_ITConfig(SAMPLE_TIM, TIM_IT_Update, ENABLE);            //允许中断更新
    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = SAMPLE_TIM_IRQn;       //TIM2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //子优先级2级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                             //初始化NVIC寄存器

    TIM_Cmd(SAMPLE_TIM, ENABLE);      //使能TIM2
}

void SAMPLE_TIM_IRQHandler(void)      //TIM中断
{
    float vol;
 
    if(TIM_GetITStatus(SAMPLE_TIM, TIM_IT_Update) != RESET)     //检查TIM更新中断是否发生
    {
        vol = Get_Battery_Voltage();
        vol_kf = KF_Filter(vol);
        printf("%.3f\n", vol_kf);
//        printf("%.3f, %.3f\n", vol, vol_kf);
        TIM_ClearITPendingBit(SAMPLE_TIM, TIM_IT_Update);
    }
}

