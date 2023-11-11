#include "stm32f4xx.h"                  // Device header
#include "MPU6050_Reg.h"
#include "MPU6050andI2C.h"
#include "MYI2C.h"

#define MPU6050_ADDRESS		0xD0

void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t Timeout;
	Timeout = 10000;
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
	{
		Timeout --;
		if (Timeout == 0)
		{
			break;
		}
	}
}

void MPU6050_WriteReg2(uint8_t RegAddress, uint8_t Data)//指定地址写数据
{
	I2C_GenerateSTART(I2C1, ENABLE);
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT);//检测EV5事件是否发生
	
	I2C_Send7bitAddress(I2C1, MPU6050_ADDRESS, I2C_Direction_Transmitter);//自带应答
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);//检测EV6事件是否发生
	
	I2C_SendData(I2C1, RegAddress);
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING);//检测EV8事件是否发生
	
	I2C_SendData(I2C1, Data);
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED);//检测EV8_2事件是否发生
	
	I2C_GenerateSTOP(I2C1, ENABLE);
}

uint8_t MPU6050_ReadReg2(uint8_t RegAddress)//指定地址读
{
	uint8_t Data;
	
	I2C_GenerateSTART(I2C1, ENABLE);
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT);//检测EV5事件是否发生
	
	I2C_Send7bitAddress(I2C1, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);//检测EV6事件是否发生
	
	I2C_SendData(I2C1, RegAddress);
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED);//检测EV8事件是否发生
	
	I2C_GenerateSTART(I2C1, ENABLE);
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT);//检测EV5事件是否发生
	
	I2C_Send7bitAddress(I2C1, MPU6050_ADDRESS, I2C_Direction_Receiver);
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);//检测EV6事件是否发生
	
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	MPU6050_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED);
	Data = I2C_ReceiveData(I2C1);//检测EV7事件是否发生
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	
	return Data;
}

void MPU6050_2_Init(void)//持续进行数据转换
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_I2C1);
	
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C1, &I2C_InitStructure);
	
	I2C_Cmd(I2C1, ENABLE);
	
	MPU6050_WriteReg2(MPU6050_PWR_MGMT_1, 0x01);		//解除睡眠，选择陀螺仪时钟
	MPU6050_WriteReg2(MPU6050_PWR_MGMT_2, 0x00);		//6个轴均不待机
	MPU6050_WriteReg2(MPU6050_SMPLRT_DIV, 0x09);		//采样分频为10
	MPU6050_WriteReg2(MPU6050_CONFIG, 0x06);				//滤波参数最大
	MPU6050_WriteReg2(MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪最大量程
	MPU6050_WriteReg2(MPU6050_ACCEL_CONFIG, 0x18); //加速度计最大量程
}

uint8_t MPU6050_GetID2(void)
{
	return MPU6050_ReadReg2(MPU6050_WHO_AM_I);
}
//分别读取6个轴数据寄存器的高位和低位，拼接成16位的数据，再通过指针变量返回
void MPU6050_GetData2(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)//数据获取(利用指针进行变量的地址传递)
{
	uint8_t DataH, DataL;
	
	DataH = MPU6050_ReadReg2(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg2(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg2(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg2(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg2(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg2(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg2(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg2(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg2(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg2(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg2(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg2(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
