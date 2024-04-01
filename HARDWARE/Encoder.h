#ifndef _ENCODER_H
#define _ENCODER_H

extern uint8_t Encoder_TIM_CNT;
extern float Encoder_Speed;


void Encoder_TIM_Init(void);
uint16_t Encoder_Get(void);

void Encoder_TIM2_Init(void);//定时1s的时间中断
void TIM5_IRQHandler(void);



#endif
