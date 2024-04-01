#include "stm32f4xx.h"                  // Device header
#include "ULN2003.h"
#include "delay.h"

uint8_t STEPS;	// ���ڴ洢��������߹����������

void ULN2003_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = ULN_A|ULN_B|ULN_C|ULN_D;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ULN_GPIO, &GPIO_InitStructure);
	
}

void ULN_Motor_Stop(void)
{
	GPIO_ResetBits(ULN_GPIO, ULN_A|ULN_B|ULN_C|ULN_D);
}
//4�ĵ���������������
void ULN_Motor_Step(uint8_t Step_Num,uint16_t Step_delay_ms)//���3ms
{
	switch(Step_Num)
	{
		case 0:		// A
			GPIO_WriteBit(ULN_GPIO, ULN_A, Bit_SET);
			GPIO_WriteBit(ULN_GPIO, ULN_B|ULN_C|ULN_D, Bit_RESET);
		break;
		case 1:		// B
			GPIO_WriteBit(ULN_GPIO, ULN_B, Bit_SET);	
			GPIO_WriteBit(ULN_GPIO, ULN_A|ULN_C|ULN_D, Bit_RESET);
		break;			
		case 2:		// C
			GPIO_WriteBit(ULN_GPIO, ULN_C, Bit_SET);	
			GPIO_WriteBit(ULN_GPIO, ULN_A|ULN_B|ULN_D, Bit_RESET);
		break;
		case 3:		// D
			GPIO_WriteBit(ULN_GPIO, ULN_D, Bit_SET);
			GPIO_WriteBit(ULN_GPIO, ULN_A|ULN_B|ULN_C, Bit_RESET);
		break;
		default: break;
  }
	delay_ms(Step_delay_ms);	 // ��ʱ�����Ƶ���ٶ�
	ULN_Motor_Stop();	         // �ϵ磬��ֹ�������
}
//�������������ת
void Step_Rotate(Direction direction, uint32_t step, uint16_t Step_delay_ms)
{
	for(uint8_t i=0;i<step;i++)
	{
		if(direction == FORWARD) //�������
		{
			STEPS ++;
			if (STEPS > 3)
			{
				STEPS = 0;
			}
		}
		else if(direction == REVERSAL)	//�����ת
		{
			if (STEPS < 1)
			{
				STEPS = 4;
			}
			STEPS --;
		}
		ULN_Motor_Step(STEPS, Step_delay_ms);
	}
}
//�������������Ȧ��ת(4��һȦ��Loop*2048��8������4096)
void Step_Loop(Direction direction,uint8_t Loop,uint16_t Step_delay_ms)
{
	Step_Rotate(direction,Loop*2048,Step_delay_ms);
}

