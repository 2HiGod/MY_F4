#include "stm32f4xx.h" 
#include "MYI2C.h"
#include "delay.h"
#include "MPU6050.h"
#include "MPU6050_Reg.h"


void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)//指定地址写数据
{
	MYI2C_Start();;//起始
	MYI2C_SendByte(MPU6050_ADDRESS);//主机寻址(从机地址+读写位)
	MYI2C_ReceiveAck(); //接收应答
	MYI2C_SendByte(RegAddress);
	MYI2C_ReceiveAck();//接收应答//存在MPU6050的当前地址指针里，用于指定具体读写的寄存器
	MYI2C_SendByte(Data);//指定所写入指定寄存器地址下的数据
	MYI2C_ReceiveAck(); //接收应答
	MYI2C_Stop();//终止时序
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)//指定地址读
{
	uint8_t Data;
	
	MYI2C_Start();
	MYI2C_SendByte(MPU6050_ADDRESS);
	MYI2C_ReceiveAck();
	MYI2C_SendByte(RegAddress);
	MYI2C_ReceiveAck();
	 
	MYI2C_Start();
	MYI2C_SendByte(MPU6050_ADDRESS | 0x01);//变为0xD1,读写位为1
	MYI2C_ReceiveAck();
	Data = MYI2C_ReceiveByte();//接收数据
	MYI2C_SendAck(1);//给从机发送一个应答(若想多发数据，则置0)
	MYI2C_Stop();//终止时序
	
	
	return Data;
}


void MPU6050_Init(void)//持续进行数据转换
{
	MYI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);  //解除睡眠，选择陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);  //6个轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);  //采样分频为10
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);      //滤波参数最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18); //陀螺仪最大量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);//加速度计最大量程 
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}
//分别读取6个轴数据寄存器的高位和低位，拼接成16位的数据，再通过指针变量返回
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)//数据获取(利用指针进行变量的地址传递)
{
	uint8_t DataH, DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}


