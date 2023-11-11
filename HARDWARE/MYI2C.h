#ifndef __MYI2C_H
#define __MYI2C_H
#include "stm32f4xx.h" 
//用来操纵端口的函数(实现函数名称及端口号的替换)
void MYI2C_W_SCL(uint8_t BitValue);//写
void MYI2C_W_SDA(uint8_t BitValue);
uint8_t MYI2C_R_SDA(void);//读

//I2C初始化
void MYI2C_Init(void);

//I2C时基单元配置
void MYI2C_Start(void);//起始条件执行逻辑
void MYI2C_Stop(void);//终止条件执行逻辑
void MYI2C_SendByte(uint8_t Byte);//主机发送字节
uint8_t MYI2C_ReceiveByte(void);//主机接收字节
void MYI2C_SendAck(uint8_t AckBit);//发送应答
uint8_t MYI2C_ReceiveAck(void);//接收应答


#endif


