#include "stm32f4xx.h"                  // Device header
#include "Encoder.h"

uint8_t Encoder_TIM_CNT;
float Encoder_Speed;
void Encoder_TIM_Init(void)
{//����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//����GPIO
	GPIO_InitTypeDef GPIO_InitStructure;//������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//���ⲿģ��Ĭ�ϵ�ƽһ��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);
	
//	TIM_InternalClockConfig(TIM2);
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//ָ��ʱ�ӻ���
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;		//���ϼ���ģʽ�����������ӿ��йܣ����ã�
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;	//arr �Զ���װֵ(16λ�Ĵ��������̼���)
	TIM_TimeBaseInitStruct.TIM_Prescaler = 42-1; //psc ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	//��ʼ�����벶��Ԫ
	TIM_ICInitTypeDef TIM_ICInitST;
	TIM_ICStructInit(&TIM_ICInitST);//Ĭ�������ʼֵ
	TIM_ICInitST.TIM_Channel=TIM_Channel_1;//ͨ��
	TIM_ICInitST.TIM_ICFilter=0xF;//���벶���˲���
	
//	TIM_ICInitST.TIM_ICPolarity=TIM_ICPolarity_Rising;//�����ز���

	TIM_ICInit(TIM4,&TIM_ICInitST);
	TIM_ICInitST.TIM_Channel=TIM_Channel_4;//ͨ��
	TIM_ICInitST.TIM_ICFilter=0xF;//���벶���˲���
	
	TIM_ICInitST.TIM_ICPolarity=TIM_ICPolarity_Rising;//�����ز���

	TIM_ICInit(TIM4,&TIM_ICInitST);
	
	//������ģʽ
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
//	NVIC_InitTypeDef	NVIC_InitST;	         	
//	NVIC_InitST.NVIC_IRQChannel	= TIM4_IRQn; 
//	NVIC_InitST.NVIC_IRQChannelPreemptionPriority = 0x01; 
//	NVIC_InitST.NVIC_IRQChannelSubPriority = 0x02; 
//	NVIC_InitST.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitST);
//	
//	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������жϺͲ����ж� 
	TIM_Cmd(TIM4, ENABLE); 	//ʹ�ܶ�ʱ��3
	
	TIM_SetCounter(TIM4,0);//��ʼ��CNT`
	
	Encoder_TIM2_Init();
}

//void TIM4_IRQHander(void)
//{
//	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == 1)
//	{
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//	}
//}


uint16_t Encoder_Get(void)
{
	return TIM_GetCounter(TIM4);
}

void Encoder_TIM2_Init(void)//��ʱ1s��ʱ���ж�
{
	NVIC_InitTypeDef	NVIC_InitST;	         	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	//����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
		TIM_InternalClockConfig(TIM5);//�������ӿڻ��й�ʱ��
	//����ʱ����Ԫ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//ָ��ʱ�ӻ���
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;		//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;	//arr �Զ���װֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8400-1; //psc ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//��������ж�
	
	NVIC_InitST.NVIC_IRQChannel	= TIM5_IRQn; 
	NVIC_InitST.NVIC_IRQChannelPreemptionPriority = 0x02; 
	NVIC_InitST.NVIC_IRQChannelSubPriority = 0x03; 
	NVIC_InitST.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitST);
	
	TIM_Cmd(TIM5, ENABLE); 	//ʹ�ܶ�ʱ��2
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET)
	{
		Encoder_TIM_CNT=TIM_GetCounter(TIM4);
		TIM4 -> CNT=0;
		Encoder_Speed=Encoder_TIM_CNT*42/(13*20*2);
		
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	}
	
}








