#ifndef __SERIAL_H
#define __SERIAL_H
#include "stm32f4xx.h"                  // Device header
#include <stdio.h>            
#include <stdarg.h> 

extern uint8_t Serial_RxFlag;
extern char Serial_RxPacket[8];
extern uint8_t Data_text;


void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);


void Datapack(void);//执行功能数据包

#endif

