#include "spi.h"

SPI_InitTypeDef SPI_InitType;

void SPIx_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SPIx_RCC | RCC_APB2Periph_SPI1, ENABLE);		//GPIOA,SPI1使能

	GPIO_InitStructure.GPIO_Pin = SPIx_SCK | SPIx_MISO | SPIx_MOSI;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPIx_GPIO, &GPIO_InitStructure);						//GPIO初始化
	GPIO_SetBits(SPIx_GPIO, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);	//IO输出高
	
	SPI_InitType.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//SPI设置全双工
	SPI_InitType.SPI_Mode = SPI_Mode_Master;							//SPI设置为主SPI
	SPI_InitType.SPI_CPOL = SPI_CPOL_High;								//稳态时钟高
	SPI_InitType.SPI_CPHA = SPI_CPHA_2Edge;								//数据捕获于第二个时钟沿
	SPI_InitType.SPI_DataSize = SPI_DataSize_8b;						//八位帧结构
	SPI_InitType.SPI_NSS = SPI_NSS_Soft;								//NSS信号由软件控制
	SPI_InitType.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//预分频256
	SPI_InitType.SPI_FirstBit = SPI_FirstBit_MSB;						//传输数据从MSE位开始
	SPI_InitType.SPI_CRCPolynomial = 7;									//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitType);										//初始化SPI1
	
	SPI_Cmd(SPI1, ENABLE);		//使能SPI1外设
	
	SPIx_ReadWriteByte(0xff);	//
}

//SPI速度设置函数
//SpeedSet:
//SPI_BaudPrescaler_2 2分频		(SPI 36M SYS 72M)
//SPI_BaudPrescaler_8 8分频		(SPI 9M SYS 72M)
//SPI_BaudPrescaler_16 16分频	(SPI 4.5M SYS 72M)
//SPI_BaudPrescaler_256 256分频	(SPI 281.25K SYS 72M)
void SPI1_SetSpeed(u8 SpeedSet)
{
	SPI_InitType.SPI_BaudRatePrescaler = SpeedSet;
	SPI_Init(SPI1, &SPI_InitType);
	SPI_Cmd(SPI1, ENABLE);
}

//SPIx:读取一个字节
//TxData:要写入的字节
//返回值：读取到的字节
u8 SPIx_ReadWriteByte(u8 TxData)
{
	u8 retry;
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)		//检查指定SPI的发送缓存空标志位
	{
		retry++;
		if(retry >= 200)
			return 0;
	}
	SPI_I2S_SendData(SPI1, TxData);			//通过外设发送一个数据
	retry = 0;
	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)		//检查指定SPI的接受缓存非空标志位
	{
		retry++;
		if(retry >= 200)
			return 0;
	}
	return SPI_I2S_ReceiveData(SPI1);		//返回SPI接受到的数据		
}





