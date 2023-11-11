#ifndef __MYI2C_H
#define __MYI2C_H
#include "stm32f4xx.h" 
//�������ݶ˿ڵĺ���(ʵ�ֺ������Ƽ��˿ںŵ��滻)
void MYI2C_W_SCL(uint8_t BitValue);//д
void MYI2C_W_SDA(uint8_t BitValue);
uint8_t MYI2C_R_SDA(void);//��

//I2C��ʼ��
void MYI2C_Init(void);

//I2Cʱ����Ԫ����
void MYI2C_Start(void);//��ʼ����ִ���߼�
void MYI2C_Stop(void);//��ֹ����ִ���߼�
void MYI2C_SendByte(uint8_t Byte);//���������ֽ�
uint8_t MYI2C_ReceiveByte(void);//���������ֽ�
void MYI2C_SendAck(uint8_t AckBit);//����Ӧ��
uint8_t MYI2C_ReceiveAck(void);//����Ӧ��


#endif


