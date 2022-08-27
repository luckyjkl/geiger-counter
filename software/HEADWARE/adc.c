#include "adc.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "OLED.h"

float R1 = 4700;
float R2 = 1000;
float Vref = 3.3;
extern __IO float vol_kf;

void Battery_ADC_Init()
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(Battery_GPIO_RCC | Battery_ADC_RCC, ENABLE);		//使能ADC时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);		//设置ADC分频因子8，72M/8=9,,ADC最大频率不能超过14M

	//PA1作为模拟输入的引脚
	GPIO_InitStructure.GPIO_Pin     = Battery_ADC_Pin;
	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AIN;        //模拟输入
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_2MHz;
	GPIO_Init(Battery_ADC_GPIO, &GPIO_InitStructure);

	ADC_DeInit(Battery_ADC);		//复位ADC,将外设外设ADC的所有寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode              = ADC_Mode_Independent;			//独立模式
	ADC_InitStructure.ADC_ScanConvMode      = DISABLE;				        //单次转换模式
    ADC_InitStructure.ADC_ContinuousConvMode= ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None;    //启动由软件触发，而不是由外部触发
	ADC_InitStructure.ADC_DataAlign         = ADC_DataAlign_Right;		    //ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel      = 1;						    //顺序进行规则转换的ADC通道的数目
	ADC_Init(Battery_ADC, &ADC_InitStructure);							    //ADC初始化

	ADC_Cmd(Battery_ADC, ENABLE);						//使能ADC
//	ADC_ResetCalibration(Battery_ADC);					//开启复位校准
//	while(ADC_GetResetCalibrationStatus(Battery_ADC));	//等待复位结束
//	ADC_StartCalibration(Battery_ADC);					//开启ADC校准
//	while(ADC_GetCalibrationStatus(Battery_ADC));		//等待校准结束
}

//获得ADC值
//ch:通道值0~3
u16 Get_adc(u8 ch)
{
	//设置指定ADC的规则通组通道，设置转化顺序和采样时间
	ADC_RegularChannelConfig(Battery_ADC, ch, 1, ADC_SampleTime_239Cycles5);		//通道，规则采样顺序值为1，采样时间为239.5周期
	ADC_SoftwareStartConvCmd(Battery_ADC, ENABLE);          //使能指定的ADC软件转换
	while(!ADC_GetFlagStatus(Battery_ADC, ADC_FLAG_EOC));	//等待转换结束
    
	return ADC_GetConversionValue(Battery_ADC);			    //返回最近一次的ADC规则组的转换结果
}

float Get_Battery_Voltage()
{
	u32 temp_val = 0;
	u8 t;
    float battery_voltage;
//    temp_val = Get_adc(Battery_ADC_Channel);
	for(t = 0; t < 50; t++)
	{
		temp_val += Get_adc(Battery_ADC_Channel);
//		delay_us(200);
	}
	temp_val = (u32)((float)temp_val / 50.0);
//    battery_voltage = (temp_val / 4095.0) * Vref;
    battery_voltage = (temp_val / 4095.0) * Vref * 1.12 * (R1 + R2) / R2;
//    printf("%.3f\n", battery_voltage);
    
    return battery_voltage;
}

void OLED_Show_Voltage()
{
    char vol_str[10];
    
    sprintf(vol_str, "BAT:%.2fV", vol_kf);
    OLED_ShowString(56, 2, (uint8_t*)vol_str);
}
