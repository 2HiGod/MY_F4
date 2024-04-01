#ifndef __DIRECTION_H
#define __DIRECTION_H
#include "stm32f4xx.h"                  // Device header


#define DIR_PIN GPIO_Pin_0
#define MOTOR_PORT GPIOG

typedef enum {
  MOTOR_FORWARD,
  MOTOR_BACKWARD
} MotorDIR;
//MotorDirection motorDirection = MOTOR_FORWARD;  // 初始方向为正转

void set_MotorDIR(MotorDIR direction);
void MotorDirection_Init(void);


#endif

