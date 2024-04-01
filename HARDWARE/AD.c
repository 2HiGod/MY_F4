#include "stm32f4xx.h"                  // Device header
#include "delay.h"
#include "AD.h"

/*
	ADC3��4,5,6,7ͨ���ֱ��ӦPF6,7,8,9
*/
void AD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	//��ʼ��ADC_CCR�Ĵ���
	
	ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;//DMAʧ��
	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ 21MHz
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;//���������׶�֮�����ʱ5��ʱ��
	ADC_CommonInit(&ADC_CommonInitStruct);
	//��ʼ��ADC����
	ADC_InitStructure.ADC_Resolution=ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;//��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStructure.ADC_NbrOfConversion=1;//ͨ����Ŀ
	ADC_Init(ADC3, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC3, ADC_Channel_4, 1, ADC_SampleTime_480Cycles );//���ͨ��,����ʱ��480
	ADC_RegularChannelConfig(ADC3, ADC_Channel_5, 1, ADC_SampleTime_480Cycles );//���ͨ��
	ADC_RegularChannelConfig(ADC3, ADC_Channel_6, 1, ADC_SampleTime_480Cycles );//���ͨ��
	ADC_RegularChannelConfig(ADC3, ADC_Channel_7, 1, ADC_SampleTime_480Cycles );//���ͨ��
	
	ADC_Cmd(ADC3, ENABLE);
}

uint16_t  Get_ADC(uint8_t Channel)//���ĳ��ͨ��ֵ 
{
	
	
	ADC_SoftwareStartConv(ADC3);	
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));
 
	return ADC_GetConversionValue(ADC3);
}

uint16_t Get_ADC_average(uint8_t Channel,uint8_t times)//�õ�ĳ��ͨ����������������ƽ��ֵ  
{
	
	uint32_t temp_val=0;
	uint8_t i;
	for(i=0;i<times;i++)
	{
		temp_val+=Get_ADC(Channel);
		delay_ms(5);
	}
	return temp_val/times;
}
