#include "stm32f4xx.h"                  // Device header
#include "SR04.h"

//������

/*
����˵����
PC6  -- TRIG(���)
PC7  -- ECHO(����)
*/
void Sr04_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//ʹ�ܶ�ʱ��ʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_6;		
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;		//�������
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;		//�������
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;		//�ٶ�
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;			//����
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_7;				
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;				//����
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL;			//����
	GPIO_Init(GPIOC, &GPIO_InitStruct);	
	


	TIM_TimeBaseInitStruct.TIM_Period		= 50000-1; 				//���ؼĴ�����
	TIM_TimeBaseInitStruct.TIM_Prescaler	= 83;   				//84��Ƶ 84MHZ/84 = 1MHZ ��һ��������1us
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;			//��Ƶ����
	//��ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

	//��ʹ�ܶ�ʱ����
	TIM_Cmd(TIM3, DISABLE);	

}

uint16_t Get_Sr04_Value(void)
{
	uint16_t t = 0;
	uint16_t distance;
	uint16_t count = 0;
	
	
	
	//�����ź�
	TRIG  = 0;
	delay_us(5);
	TRIG  = 1;
	delay_us(20);
	TRIG  = 0;

	//����CNTΪ0
	TIM3->CNT = 0;
	
	//�ȴ��ߵ�ƽ����,������ʱ����
	while( PCin(7) == 0)
	{
		t++;
		delay_us(10);
	
		//����ȴ�5msδ�ܵȴ��ߵ�ƽ���򷵻�
		if(t >= 500)
			return 0;
	}

	//������ʱ��
	TIM_Cmd(TIM3, ENABLE);	
	
	t = 0;
	//�ȴ��͵�ƽ������������ʱ����
	while( PCin(7) == 1 )
	{
		t++;
		delay_us(20);
	
		//����ȴ�24ms��24ms�����ľ���Ϊ413cm�ˣ��ֲ���˵��ԶΪ40cmm����ȡ��ֵ��δ�ܵȴ��͵�ƽ���򷵻�
		if(t >= 1200)
			return 0;		
	}

	//��ȡ��ʱ����CNTֵ
	//count = TIM_GetCounter(TIM3);
	count = TIM3->CNT;
	
	//�رն�ʱ��
	TIM_Cmd(TIM3, DISABLE);	
	
	//ͨ����ʱ����CNTֵ���������

	distance = count/58;

	return distance;
}

