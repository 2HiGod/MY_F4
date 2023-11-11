#ifndef __SR04_H
#define __SR04_H
#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"

/*******************************
引脚说明：
PA2  -- TRIG(输出)
PA3  -- ECHO(输入)
*******************************/

#define TRIG   PCout(6)
#define ECHO   PCin(7)


void Sr04_Init(void);
uint16_t Get_Sr04_Value(void);

#endif

