#ifndef __ULN2003_H
#define __ULN2003_H

// 电机的旋转方向
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
//4拍单相整步驱动函数
void ULN_Motor_Step(uint8_t Step_Num,uint16_t Step_delay_ms);
//步进电机按步旋转
void Step_Rotate(Direction direction, uint32_t step, uint16_t Step_delay_ms);
//步进电机按整数圈旋转(4拍一圈是Loop*2048，8拍则是4096)
void Step_Loop(Direction direction,uint8_t Loop,uint16_t Step_delay_ms);



#endif

