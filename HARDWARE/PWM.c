#include "stm32f4xx.h" 
#include "PWM.h"



void Servo_PWM_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//指定时钟划分
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;	//arr 自动重装值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 84-1; //psc 时钟预分频数
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	
	//PWM配置
	TIM_OCInitTypeDef TIM_OCInitStruct;
//	TIM_OCStructInit(&TIM_OCInitStruct);//给函数赋初始值
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//PWM1 计数值>有效值时有效电平	
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//有效电平为高
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;		//输出比较使能
	TIM_OCInitStruct.TIM_Pulse=0;    //ccr 捕获比较值
	
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);   //定时器通道初始化
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);
	
//	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);				//启用外设加载寄存器
//	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);						//使能自动重装载寄存器允许位	
	
	TIM_Cmd(TIM2, ENABLE); 	//开启定时器2
	
}

void Motor_PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//指定时钟划分
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;	//arr 自动重装值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 840-1; //psc 时钟预分频数
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	
	
	//PWM配置
	TIM_OCInitTypeDef TIM_OCInitStruct;
//	TIM_OCStructInit(&TIM_OCInitStruct);//给函数赋初始值
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//PWM1 计数值>有效值时有效电平	
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//有效电平为高
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;		//输出比较使能
	TIM_OCInitStruct.TIM_Pulse=0;    //ccr 捕获比较值
	
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);   //定时器通道初始化
	TIM_OC2Init(TIM1,&TIM_OCInitStruct);
	
//	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);				//启用外设加载寄存器
//	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);

	
	TIM_ARRPreloadConfig(TIM1,ENABLE);						//使能自动重装载寄存器允许位	
	
	TIM_Cmd(TIM1, ENABLE); 	//开启定时器2
}

void PWM_Servo(u32 servo_Pin,float angle)
{
	u32 compare=(angle/180)*2000+500;//compare设置CCR 500-2500对应0.5-2.5ms ;
	
	if(servo_Pin==0)
	  TIM_SetCompare1(TIM2,compare);
	if(servo_Pin==1)
		TIM_SetCompare2(TIM2,compare);
	if(servo_Pin==2)
		TIM_SetCompare3(TIM2,compare);
	if(servo_Pin==3)
		TIM_SetCompare4(TIM2,compare);
}

void PWM_Motor(u32 Motor_compare)//电机PWM
{
	TIM_SetCompare1(TIM1,Motor_compare);
	TIM_SetCompare2(TIM1,Motor_compare);
}

