#ifndef __PWM_H
#define __PWM_H



typedef enum {
  ENCODER_FORWARD,//正转
  ENCODER_BACKWARD//反转
} ENCODERDIR;

void Servo_PWM_Init(void);
void Motor_PWM_Init(void);

void PWM_Servo(u32 servo_Pin,float compare);
void PWM_Motor(u32 Motor_compare);

void PWM_SetPrescaler(uint16_t Prescaler);

void Encoder_PWM_Init(void);//L298N驱动编码器电机PWM
void PWM_Encoder(ENCODERDIR DIR,uint32_t SPEED);//L298N驱动编码器电机PWM（转速及方向）



#endif


