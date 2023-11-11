#include "stm32f4xx.h" 
#include "Motor.h"
#include "PWM.h"

void Motor_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	Motor_PWM_Init();
}

void Motor_Speed(int8_t Speed)//设置转机速度及方向
{
	if(Speed >=0)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_1);
		GPIO_ResetBits(GPIOD,GPIO_Pin_0);
		PWM_Motor(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_0);
		GPIO_ResetBits(GPIOD,GPIO_Pin_1);
		PWM_Motor(-Speed);
	}
}
