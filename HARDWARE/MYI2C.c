#include "stm32f4xx.h" 
#include "MYI2C.h"
#include "delay.h"

//I2C初始化
void MYI2C_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9);
}
/*
软件I2C

*/
//用来操纵端口的函数(实现函数名称及端口号的替换)
void MYI2C_W_SCL(uint8_t BitValue)//写
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_8,(BitAction)BitValue);
	delay_us(10);
}

void MYI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_9,(BitAction)BitValue);
	delay_us(10);
}

uint8_t MYI2C_R_SDA(void)//读
{
	uint8_t BitValue;
	BitValue=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9);
	delay_us(10);
	
	return BitValue;
}


//I2C时基单元配置
void MYI2C_Start(void)//起始条件执行逻辑
{
	MYI2C_W_SDA(1);
	MYI2C_W_SCL(1);//将SCL与SDA释放
	
	MYI2C_W_SDA(0);//将其拉低先SDA再SCL
	MYI2C_W_SCL(0);
}
void MYI2C_Stop(void)//终止条件执行逻辑
{
	MYI2C_W_SDA(0);
	MYI2C_W_SCL(1);//将SCL与SDA释放
	MYI2C_W_SDA(1);
}

void MYI2C_SendByte(uint8_t Byte)//主机发送字节
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MYI2C_W_SDA(Byte & 0x80 >> i);//将0x80右移i位，然后按位与的方式取出数据的某一位或某几位
		MYI2C_W_SCL(1);//驱动时钟走一个脉冲
		MYI2C_W_SCL(0);
	}
}
uint8_t MYI2C_ReceiveByte(void)//主机接收字节
{
	uint8_t i,Byte = 0x00;
	MYI2C_W_SDA(1);
	for(i=0;i<8;i++)
	{
		MYI2C_W_SCL(1);
		if(MYI2C_R_SDA() == 1)
			Byte|= (0x80 >> i);
		MYI2C_W_SCL(0);
	}
	return Byte;
}

void MYI2C_SendAck(uint8_t AckBit)//发送应答
{
		MYI2C_W_SDA(AckBit);
		MYI2C_W_SCL(1);//驱动时钟走一个脉冲
		MYI2C_W_SCL(0);
}
uint8_t MYI2C_ReceiveAck(void)//接收应答
{
	uint8_t AckBit;
	MYI2C_W_SDA(1);//主机释放SDA
	MYI2C_W_SCL(1);
	AckBit=MYI2C_R_SDA();
	MYI2C_W_SCL(0);//进入下一个时基单元
	return AckBit;
}

