#include "timer.h"
#include "led.h"
#include "beep.h"
#include "oled.h"
#include "usart.h"
#include "adc.h"
//通用定时器3中断初始化
//这里时钟选择为APB1两倍，而APB1为36M
//arr:自动重装值
//psc:时钟预分频数
//使用的是定时器3

extern int volatile Geiger_Count;
extern int volatile Last_Geiger_Count;
int volatile Count_Queue[MAX_QUEUE_LENGTH] = {0};
int volatile Count_Sum = 0;					//一分钟内总计数值
float volatile Count_Time = 0;	            //测量队列时间，单位秒
uint16_t Queue_Head = 0;				    //当前队列		
float radiation_dose = 0;
int i = 0;

void TIM3_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);        //时钟TIM3使能
    //定时器TIM3初始化
    TIM_TimeBaseStructure.TIM_Period = arr;                     //设置自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //设置时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //初始化TIM
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                  //允许中断更新
    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;             //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //子优先级2级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                             //初始化NVIC寄存器

    TIM_Cmd(TIM3, ENABLE);      //使能TIM3
}

void TIM3_IRQHandler(void)      //TIM3中断
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)       //检查TIM3更新中断是否发生
    {
        BEEP_OFF;
        i++;
        if(Count_Time < 60)
		{
			Count_Time += 0.1;
		}
		
		//构建一个循环队列，统计1分钟内的计数值，根据一分钟内的计数值统计辐射剂量
		if(Queue_Head >= MAX_QUEUE_LENGTH)
		{
			Queue_Head = 0;
		}
		Count_Sum += Geiger_Count - Count_Queue[(Queue_Head + 1) % MAX_QUEUE_LENGTH];	//计数值加上队列头减去队列尾
		Count_Queue[Queue_Head++] = Geiger_Count;									    //当前一秒内计数值入队
        
        if(Geiger_Count > 0)
        {
            Geiger_Count = 0;
            BEEP_ON;
            OLED_ShowNum(24, 2, Count_Sum, 3, 16);
            Show_Radiation_Dose();
        }
//        printf("%d\n", Geiger_Count);
//        printf("%d, %d\n", Geiger_Count, Count_Sum);
//        if(i >= 10)
//        {
//            OLED_ShowNum(24, 2, Count_Sum, 3, 16);
//            Show_Radiation_Dose();
//            OLED_Show_Voltage();
//            i = 0;
//        }
        
        OLED_ShowNum(24, 2, Count_Sum, 3, 16);
        Show_Radiation_Dose();
        OLED_Show_Voltage();
        
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
                 
//        Last_Geiger_Count = Geiger_Count;
//		Last_Geiger_Count = 0;
    }
}

void Show_Radiation_Dose(void)
{
	char temp[12];
	
//	radiation_dose = (151 / 60.0) * Geiger_Count / Count_Second;

	radiation_dose = (151 / 60.0) * (float)Count_Sum / Count_Time;
	
	sprintf(temp, "%.3fuSv/h", radiation_dose);
	OLED_ShowString(0, 4, (u8*)temp);
}
