#include "stm32f4xx.h"                  // Device header
#include "delay.h"
#include "direction.h"
#include "energize.h"
#include "Key.h"
#include "PWM.h"

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	Exti_Init();
}


uint8_t Key_GetNum(void)//按键直接控制
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0);
		delay_ms(20);
		KeyNum = 1;
	}
	
	return KeyNum;
}

void Exti_Init(void)
{

	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	//将PA0和EXTI15连接在一起
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource15);
	//外部中断的配置
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发，用于识别按键的按下
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级 2，
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //子优先级 1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

//void EXTI15_10_IRQHandler(void)
//{

//	if(EXTI_GetFlagStatus(EXTI_Line15) == SET)
// {
//		GPIO_ResetBits(GPIOC, GPIO_Pin_13);	
//	  delay_ms(100);
//	  GPIO_SetBits(GPIOC, GPIO_Pin_13);	
//	  delay_ms(100);
////		delay_ms(5000);
////		SetENA(ENERGIZE_ENABLE);
////		set_MotorDIR( MOTOR_BACKWARD);
////		PWM_Motor(10);
//	 
//		EXTI_ClearITPendingBit(EXTI_Line15);
// } 
//}


