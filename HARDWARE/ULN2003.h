#ifndef __ULN2003_H
#define __ULN2003_H

// �������ת����
typedef enum 
{
	FORWARD = 0,
	REVERSAL = 1
} Direction;


#define ULN_GPIO  GPIOD
#define ULN_A     GPIO_Pin_10
#define ULN_B     GPIO_Pin_11
#define ULN_C     GPIO_Pin_12
#define ULN_D     GPIO_Pin_13


void ULN2003_Init(void);
void ULN_Motor_Stop(void);
//4�ĵ���������������
void ULN_Motor_Step(uint8_t Step_Num,uint16_t Step_delay_ms);
//�������������ת
void Step_Rotate(Direction direction, uint32_t step, uint16_t Step_delay_ms);
//�������������Ȧ��ת(4��һȦ��Loop*2048��8������4096)
void Step_Loop(Direction direction,uint8_t Loop,uint16_t Step_delay_ms);



#endif

