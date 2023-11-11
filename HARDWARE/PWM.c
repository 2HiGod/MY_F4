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
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//ָ��ʱ�ӻ���
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;		//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;	//arr �Զ���װֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 84-1; //psc ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	
	//PWM����
	TIM_OCInitTypeDef TIM_OCInitStruct;
//	TIM_OCStructInit(&TIM_OCInitStruct);//����������ʼֵ
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//PWM1 ����ֵ>��Чֵʱ��Ч��ƽ	
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//��Ч��ƽΪ��
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;		//����Ƚ�ʹ��
	TIM_OCInitStruct.TIM_Pulse=0;    //ccr ����Ƚ�ֵ
	
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);   //��ʱ��ͨ����ʼ��
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);
	
//	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);				//����������ؼĴ���
//	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);						//ʹ���Զ���װ�ؼĴ�������λ	
	
	TIM_Cmd(TIM2, ENABLE); 	//������ʱ��2
	
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
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//ָ��ʱ�ӻ���
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;		//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;	//arr �Զ���װֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 840-1; //psc ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	
	
	//PWM����
	TIM_OCInitTypeDef TIM_OCInitStruct;
//	TIM_OCStructInit(&TIM_OCInitStruct);//����������ʼֵ
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//PWM1 ����ֵ>��Чֵʱ��Ч��ƽ	
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//��Ч��ƽΪ��
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;		//����Ƚ�ʹ��
	TIM_OCInitStruct.TIM_Pulse=0;    //ccr ����Ƚ�ֵ
	
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);   //��ʱ��ͨ����ʼ��
	TIM_OC2Init(TIM1,&TIM_OCInitStruct);
	
//	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);				//����������ؼĴ���
//	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);

	
	TIM_ARRPreloadConfig(TIM1,ENABLE);						//ʹ���Զ���װ�ؼĴ�������λ	
	
	TIM_Cmd(TIM1, ENABLE); 	//������ʱ��2
}

void PWM_Servo(u32 servo_Pin,float angle)
{
	u32 compare=(angle/180)*2000+500;//compare����CCR 500-2500��Ӧ0.5-2.5ms ;
	
	if(servo_Pin==0)
	  TIM_SetCompare1(TIM2,compare);
	if(servo_Pin==1)
		TIM_SetCompare2(TIM2,compare);
	if(servo_Pin==2)
		TIM_SetCompare3(TIM2,compare);
	if(servo_Pin==3)
		TIM_SetCompare4(TIM2,compare);
}

void PWM_Motor(u32 Motor_compare)//���PWM
{
	TIM_SetCompare1(TIM1,Motor_compare);
	TIM_SetCompare2(TIM1,Motor_compare);
}

