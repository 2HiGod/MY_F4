#ifndef __KEY_H
#define __KEY_H


void Key_Init(void);
void Exti_Init(void);
void EXTI15_10_IRQHandler(void);

uint8_t Key_GetNum(void);




#endif

