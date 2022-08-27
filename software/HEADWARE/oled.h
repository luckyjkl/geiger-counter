//  功能描述   : OLED 接口演示例程(stm31f1系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PB13（SCL）
//              D1   接PB15（SDA）
//              RES  接PC10
//              DC   接PB2              
//              ----------------------------------------------------------------
// 修改历史   :	2018-10-4 改为硬件spi驱动
// 日    期   : 
// 作    者   :

//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f10x.h"
#include "stdlib.h"	    	
//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 	0
#define SIZE 		16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

#define	OLED_SPI_RCC	RCC_APB2Periph_GPIOB
#define OLED_SPI_GPIO	GPIOB
#define OLED_SPI_SCK	GPIO_Pin_13
#define OLED_SPI_MISO	GPIO_Pin_14
#define OLED_SPI_MOSI	GPIO_Pin_15
#define OLED_SPI		SPI2

#define OLED_DC_RCC		RCC_APB2Periph_GPIOA
#define	OLED_DC_GPIO	GPIOA
#define OLED_DC			GPIO_Pin_8

#define OLED_RST_RCC	RCC_APB2Periph_GPIOA
#define OLED_RST_GPIO	GPIOA
#define OLED_RST		GPIO_Pin_11

#define OLED_CS_RCC		RCC_APB2Periph_GPIOB
#define OLED_CS_GPIO	GPIOB
#define OLED_CS			GPIO_Pin_12

//-----------------测试LED端口定义---------------- 
//#define LED_ON GPIO_ResetBits(GPIOB,GPIO_Pin_8)//DC
//#define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_8)

//-----------------OLED端口定义----------------  					   


//#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)	//CLK
//#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

//#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)	//DIN
//#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define OLED_RST_Clr() GPIO_ResetBits(OLED_RST_GPIO,OLED_RST)	//RST
#define OLED_RST_Set() GPIO_SetBits(OLED_RST_GPIO,OLED_RST)

#define OLED_DC_Clr() GPIO_ResetBits(OLED_DC_GPIO, OLED_DC)		//DC
#define OLED_DC_Set() GPIO_SetBits(OLED_DC_GPIO, OLED_DC)

#define OLED_CS_Clr() GPIO_ResetBits(OLED_CS_GPIO, OLED_CS)		//DC
#define OLED_CS_Set() GPIO_SetBits(OLED_CS_GPIO, OLED_CS)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);
//void OLED_Write_Cmd(u8 cmd);
//void OLED_Write_Data(u8 dat);
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void SPI_OLED_Init(void);
void SPI_OLED_WR_Byte(u8 data);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



