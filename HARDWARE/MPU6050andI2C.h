#ifndef __MPU6050ANDI2C_H
#define __MPU6050ANDI2C_H
#include "stm32f4xx.h" 

void MPU6050_WriteReg2(uint8_t RegAddress,uint8_t Data);//ָ����ַд����
uint8_t MPU6050_ReadReg2(uint8_t RegAddress);//ָ����ַ��
void MPU6050_2_Init(void);
uint8_t MPU6050_GetID2(void);
void MPU6050_GetData2(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
													int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ);//���ݻ�ȡ(����ָ����б����ĵ�ַ����)
#endif


