#include "stm32f4xx.h" 
#include "MYI2C.h"
#include "delay.h"
#include "MPU6050.h"
#include "MPU6050_Reg.h"


void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)//ָ����ַд����
{
	MYI2C_Start();;//��ʼ
	MYI2C_SendByte(MPU6050_ADDRESS);//����Ѱַ(�ӻ���ַ+��дλ)
	MYI2C_ReceiveAck(); //����Ӧ��
	MYI2C_SendByte(RegAddress);
	MYI2C_ReceiveAck();//����Ӧ��//����MPU6050�ĵ�ǰ��ַָ�������ָ�������д�ļĴ���
	MYI2C_SendByte(Data);//ָ����д��ָ���Ĵ�����ַ�µ�����
	MYI2C_ReceiveAck(); //����Ӧ��
	MYI2C_Stop();//��ֹʱ��
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)//ָ����ַ��
{
	uint8_t Data;
	
	MYI2C_Start();
	MYI2C_SendByte(MPU6050_ADDRESS);
	MYI2C_ReceiveAck();
	MYI2C_SendByte(RegAddress);
	MYI2C_ReceiveAck();
	 
	MYI2C_Start();
	MYI2C_SendByte(MPU6050_ADDRESS | 0x01);//��Ϊ0xD1,��дλΪ1
	MYI2C_ReceiveAck();
	Data = MYI2C_ReceiveByte();//��������
	MYI2C_SendAck(1);//���ӻ�����һ��Ӧ��(����෢���ݣ�����0)
	MYI2C_Stop();//��ֹʱ��
	
	
	return Data;
}


void MPU6050_Init(void)//������������ת��
{
	MYI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);  //���˯�ߣ�ѡ��������ʱ��
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);  //6�����������
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);  //������ƵΪ10
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);      //�˲��������
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18); //�������������
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);//���ٶȼ�������� 
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}
//�ֱ��ȡ6�������ݼĴ����ĸ�λ�͵�λ��ƴ�ӳ�16λ�����ݣ���ͨ��ָ���������
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)//���ݻ�ȡ(����ָ����б����ĵ�ַ����)
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


