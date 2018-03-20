<<<<<<< HEAD
#ifndef __ADC_H
#define	__ADC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "stm32f10x.h"
#include "Arduino.h"


// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响

// 转换通道个数
#define ADC_CHANNEL_NUM 8
extern uint16_t ADC_ConvertedValue[ADC_CHANNEL_NUM];//ADC DMA Buffer

// ADC1 对应 DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能


/**************************函数声明********************************/
void ADCx_DMA_Init(void);
void ADCx_Init(void);

uint16_t Get_DMA_ADC(uint8_t channel);
uint16_t Get_ADC(uint16_t channel);
uint16_t ADC_Pin_Read(uint8_t Pin);


#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
=======
#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOA


// 转换通道个数
#define    NOFCHANEL					 8

#define    ADC_PIN1                      GPIO_Pin_0
#define    ADC_CHANNEL1                  ADC_Channel_0

#define    ADC_PIN2                      GPIO_Pin_1
#define    ADC_CHANNEL2                  ADC_Channel_1

#define    ADC_PIN3                      GPIO_Pin_2
#define    ADC_CHANNEL3                  ADC_Channel_2

#define    ADC_PIN4                      GPIO_Pin_3
#define    ADC_CHANNEL4                  ADC_Channel_3

#define    ADC_PIN5                      GPIO_Pin_4
#define    ADC_CHANNEL5                  ADC_Channel_4

#define    ADC_PIN6                      GPIO_Pin_5
#define    ADC_CHANNEL6                  ADC_Channel_5

#define    ADC_PIN7                      GPIO_Pin_6
#define    ADC_CHANNEL7                  ADC_Channel_6

#define    ADC_PIN8                      GPIO_Pin_7
#define    ADC_CHANNEL8                  ADC_Channel_7


// ADC1 对应 DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1


/**************************函数声明********************************/
void ADCx_DMA_Init(void);
void ADCx_Init(void);

uint16_t Get_DMA_ADC(uint8_t channel);
uint16_t Get_ADC(uint16_t channel);
uint16_t ADC_Pin_Read(uint8_t Pin);


#endif /* __ADC_H */

>>>>>>> 301cbab54594d1de84f6a7e456407b3a84e8d255
