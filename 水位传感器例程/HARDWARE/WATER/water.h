#ifndef __WATER_H
#define	__WATER_H
#include "stm32f10x.h"
#include "adcx.h"
#include "delay.h"
#include "math.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	水位传感器h文件                   
 * 版本			: V1.0
 * 日期			: 2025.1.27
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码								
 * IP账号		:	辰哥单片机设计（同BILIBILI|抖音|快手|小红书|CSDN|公众号|视频号等）
 * 作者			:	辰哥 
 * 工作室		: 异方辰电子工作室
 * 讲解视频	:	https://www.bilibili.com/video/BV1nxF3eRErF/?share_source=copy_web
 * 官方网站	:	www.yfcdz.cn

**********************BEGIN***********************/

#define WATER_READ_TIMES	10  //WATER传感器ADC循环读取次数

//模式选择	
//模拟AO:	1
//数字DO:	0
#define	MODE 	0

/***************根据自己需求更改****************/
// WATER GPIO宏定义
#if MODE
#define		WATER_AO_GPIO_CLK								RCC_APB2Periph_GPIOA
#define 	WATER_AO_GPIO_PORT							GPIOA
#define 	WATER_AO_GPIO_PIN								GPIO_Pin_0
#define   ADC_CHANNEL               			ADC_Channel_0	// ADC 通道宏定义

#else
#define		WATER_DO_GPIO_CLK								RCC_APB2Periph_GPIOA
#define 	WATER_DO_GPIO_PORT							GPIOA
#define 	WATER_DO_GPIO_PIN								GPIO_Pin_1			

#endif
/*********************END**********************/


void WATER_Init(void);
uint16_t WATER_GetData(void);

#endif /* __WATER_H */

