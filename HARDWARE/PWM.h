#ifndef __PWM_H
#define __PWM_H


void Servo_PWM_Init(void);
void Motor_PWM_Init(void);

void PWM_Servo(u32 servo_Pin,float compare);
void PWM_Motor(u32 Motor_compare);





#endif


