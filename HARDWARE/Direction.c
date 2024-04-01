#include "stm32f4xx.h"                  // Device header
#include "direction.h"

void MotorDirection_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
}


// 步进电机方向
void set_MotorDIR(MotorDIR direction) 
{		

	if (direction == MOTOR_FORWARD) 
		{
			GPIO_ResetBits(MOTOR_PORT, DIR_PIN);
		}
	else 
		{
			GPIO_SetBits(MOTOR_PORT, DIR_PIN);
		}
}

