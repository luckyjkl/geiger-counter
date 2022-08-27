#include "stm32f10x.h"
#include <stdio.h>
#include "oled.h"
#include "pwm.h"
#include "exti.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"
#include "beep.h"
#include "adc.h"
#include "sample_timer.h"

//151CPM=1uSv/h,计数和辐射量转换公式

//extern int Geiger_Count;
//extern int Last_Geiger_Count;
//extern float volatile Count_Time;
extern int volatile Count_Sum;
////float radiation_dose = 0;
//extern char volatile Count_Queue[MAX_QUEUE_LENGTH];

int main()
{
//	u16 volatile pwmval;	
//	pwmval = 13999;
	delay_init();
	uart_init(115200);
	EXTIX_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     //设置中断分组
	SPI_OLED_Init();
    Battery_ADC_Init();
	
	TIM3_Init(9999, 719);			//频率100K，计数时间0.1s
    Sample_Timer_Init();
	BEEP_Init();					//蜂鸣器初始化
	
	OLED_ShowString(0, 0, "Geiger Counter");
	OLED_ShowString(0, 2, "CPM");
    
    OLED_ShowNum(24, 2, Count_Sum, 3, 16);
    Show_Radiation_Dose();
    OLED_Show_Voltage();
	
	while(1)
	{
//		OLED_ShowNum(24, 2, Count_Sum, 3, 16);
//		Show_Radiation_Dose();
//		if(Last_Geiger_Count < Geiger_Count)
//		{
//			Last_Geiger_Count = Geiger_Count;
//			BEEP_ON;
//		}
//		delay_ms(100);
//		BEEP_OFF;
//		printf("test\r\n");
	}
}


