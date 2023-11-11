#ifndef __AD_H
#define __AD_H

void AD_Init(void);
uint16_t  Get_ADC(uint8_t Channel);//获得某个通道值 
uint16_t Get_ADC_average(uint8_t Channel,uint8_t times);//得到某个通道给定次数采样的平均值  



#endif
