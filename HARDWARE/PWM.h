#ifndef __PWM_H
#define __PWM_H



typedef enum {
  ENCODER_FORWARD,//��ת
  ENCODER_BACKWARD//��ת
} ENCODERDIR;

void Servo_PWM_Init(void);
void Motor_PWM_Init(void);

void PWM_Servo(u32 servo_Pin,float compare);
void PWM_Motor(u32 Motor_compare);

void PWM_SetPrescaler(uint16_t Prescaler);

void Encoder_PWM_Init(void);//L298N�������������PWM
void PWM_Encoder(ENCODERDIR DIR,uint32_t SPEED);//L298N�������������PWM��ת�ټ�����



#endif


