#include "stm32f4xx.h" 
#include "MYI2C.h"
#include "delay.h"

//I2C��ʼ��
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
���I2C

*/
//�������ݶ˿ڵĺ���(ʵ�ֺ������Ƽ��˿ںŵ��滻)
void MYI2C_W_SCL(uint8_t BitValue)//д
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_8,(BitAction)BitValue);
	delay_us(10);
}

void MYI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOD,GPIO_Pin_9,(BitAction)BitValue);
	delay_us(10);
}

uint8_t MYI2C_R_SDA(void)//��
{
	uint8_t BitValue;
	BitValue=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9);
	delay_us(10);
	
	return BitValue;
}


//I2Cʱ����Ԫ����
void MYI2C_Start(void)//��ʼ����ִ���߼�
{
	MYI2C_W_SDA(1);
	MYI2C_W_SCL(1);//��SCL��SDA�ͷ�
	
	MYI2C_W_SDA(0);//����������SDA��SCL
	MYI2C_W_SCL(0);
}
void MYI2C_Stop(void)//��ֹ����ִ���߼�
{
	MYI2C_W_SDA(0);
	MYI2C_W_SCL(1);//��SCL��SDA�ͷ�
	MYI2C_W_SDA(1);
}

void MYI2C_SendByte(uint8_t Byte)//���������ֽ�
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MYI2C_W_SDA(Byte & 0x80 >> i);//��0x80����iλ��Ȼ��λ��ķ�ʽȡ�����ݵ�ĳһλ��ĳ��λ
		MYI2C_W_SCL(1);//����ʱ����һ������
		MYI2C_W_SCL(0);
	}
}
uint8_t MYI2C_ReceiveByte(void)//���������ֽ�
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

void MYI2C_SendAck(uint8_t AckBit)//����Ӧ��
{
		MYI2C_W_SDA(AckBit);
		MYI2C_W_SCL(1);//����ʱ����һ������
		MYI2C_W_SCL(0);
}
uint8_t MYI2C_ReceiveAck(void)//����Ӧ��
{
	uint8_t AckBit;
	MYI2C_W_SDA(1);//�����ͷ�SDA
	MYI2C_W_SCL(1);
	AckBit=MYI2C_R_SDA();
	MYI2C_W_SCL(0);//������һ��ʱ����Ԫ
	return AckBit;
}

