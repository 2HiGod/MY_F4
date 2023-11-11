#ifndef __MPU6050_H
#define __MPU6050_H
#include "stm32f4xx.h" 

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data);//指定地址写数据
uint8_t MPU6050_ReadReg(uint8_t RegAddress);//指定地址读
void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
													int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ);//数据获取(利用指针进行变量的地址传递)
#endif


