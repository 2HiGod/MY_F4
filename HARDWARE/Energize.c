#include "stm32f4xx.h"                  // Device header
#include "energize.h"

 //电机驱动器的使能
void Energize_Init(void)
{
	// 初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	
}

void SetENA(SETENA energize) 
{		

  if (energize==ENERGIZE_ENABLE) 
		{
			GPIO_SetBits(GPIOG, GPIO_Pin_1);
		} else 
		{
			GPIO_ResetBits(GPIOG, GPIO_Pin_1);
		}
}


