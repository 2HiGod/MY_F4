#include "stm32f4xx.h"                  // Device header
#include "delay.h"
#include "AD.h"

/*
	ADC3的4,5,6,7通道分别对应PF6,7,8,9
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
	
	//初始化ADC_CCR寄存器
	
	ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;//DMA失能
	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;//独立模式
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;//预分频4分频 21MHz
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延时5个时钟
	ADC_CommonInit(&ADC_CommonInitStruct);
	//初始化ADC参数
	ADC_InitStructure.ADC_Resolution=ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;//非扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//右对齐
	ADC_InitStructure.ADC_NbrOfConversion=1;//通道数目
	ADC_Init(ADC3, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC3, ADC_Channel_4, 1, ADC_SampleTime_480Cycles );//填充通道,采样时间480
	ADC_RegularChannelConfig(ADC3, ADC_Channel_5, 1, ADC_SampleTime_480Cycles );//填充通道
	ADC_RegularChannelConfig(ADC3, ADC_Channel_6, 1, ADC_SampleTime_480Cycles );//填充通道
	ADC_RegularChannelConfig(ADC3, ADC_Channel_7, 1, ADC_SampleTime_480Cycles );//填充通道
	
	ADC_Cmd(ADC3, ENABLE);
}

uint16_t  Get_ADC(uint8_t Channel)//获得某个通道值 
{
	
	
	ADC_SoftwareStartConv(ADC3);	
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));
 
	return ADC_GetConversionValue(ADC3);
}

uint16_t Get_ADC_average(uint8_t Channel,uint8_t times)//得到某个通道给定次数采样的平均值  
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
