#ifndef __MPU6050_REG_H
#define __MPU6050_REG_H
#include "stm32f4xx.h"                  // Device header


#define MPU6050_ADDRESS      0xD0
/*
	MPU6050�Ĵ�����ַ
*/
#define	MPU6050_SMPLRT_DIV		0x19   //�����ʷ�Ƶ(���������������)ԽСԽ��
#define	MPU6050_CONFIG			0x1A     //���üĴ���
#define	MPU6050_GYRO_CONFIG		0x1B   //���������üĴ���
#define	MPU6050_ACCEL_CONFIG	0x1C   //���ٶȼ����üĴ���
//���ݼĴ���                                     
#define	MPU6050_ACCEL_XOUT_H	0x3B   //���ٶȼƼĴ���X��ĸ߰�λ
#define	MPU6050_ACCEL_XOUT_L	0x3C   //���ٶȼƼĴ���X��ĵͰ�λ
#define	MPU6050_ACCEL_YOUT_H	0x3D   //���ٶȼƼĴ���Y��ĸ߰�λ
#define	MPU6050_ACCEL_YOUT_L	0x3E   //���ٶȼƼĴ���Y��ĵͰ�λ
#define	MPU6050_ACCEL_ZOUT_H	0x3F   //���ٶȼƼĴ���Z��ĸ߰�λ
#define	MPU6050_ACCEL_ZOUT_L	0x40   //���ٶȼƼĴ���Z��ĵͰ�λ
#define	MPU6050_TEMP_OUT_H		0x41   //�¶ȼĴ����ĸ߰�λ
#define	MPU6050_TEMP_OUT_L		0x42   //�¶ȼĴ����ĵͰ�λ
#define	MPU6050_GYRO_XOUT_H		0x43   //�����ǼĴ���X��ĸ߰�λ
#define	MPU6050_GYRO_XOUT_L		0x44   //�����ǼĴ���X��ĵͰ�λ
#define	MPU6050_GYRO_YOUT_H		0x45   //�����ǼĴ���Y��ĸ߰�λ
#define	MPU6050_GYRO_YOUT_L		0x46   //�����ǼĴ���Y��ĵͰ�λ
#define	MPU6050_GYRO_ZOUT_H		0x47   //�����ǼĴ���Z��ĸ߰�λ
#define	MPU6050_GYRO_ZOUT_L		0x48   //�����ǼĴ���Z��ĵͰ�λ
//��Դ�Ĵ���                                    
#define	MPU6050_PWR_MGMT_1		0x6B   //��Դ����Ĵ���1
#define	MPU6050_PWR_MGMT_2		0x6C   //��Դ����Ĵ���2
#define	MPU6050_WHO_AM_I		0x75

#endif


