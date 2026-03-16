#include "water.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	水位传感器c文件                   
 * 版本			: V1.0
 * 日期			: 2024.1.27
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码								
 * IP账号		:	辰哥单片机设计（同BILIBILI|抖音|快手|小红书|CSDN|公众号|视频号等）
 * 作者			:	辰哥 
 * 工作室		: 异方辰电子工作室
 * 讲解视频	:	https://www.bilibili.com/video/BV1nxF3eRErF/?share_source=copy_web
 * 官方网站	:	www.yfcdz.cn

**********************BEGIN***********************/

void WATER_Init(void)
{
	#if MODE
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (WATER_AO_GPIO_CLK, ENABLE );	// 打开 ADC IO端口时钟
		GPIO_InitStructure.GPIO_Pin = WATER_AO_GPIO_PIN;					// 配置 ADC IO 引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// 设置为模拟输入
		
		GPIO_Init(WATER_AO_GPIO_PORT, &GPIO_InitStructure);				// 初始化 ADC IO

		ADCx_Init();
	}
	#else
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (WATER_DO_GPIO_CLK, ENABLE );	// 打开连接 传感器DO 的单片机引脚端口时钟
		GPIO_InitStructure.GPIO_Pin = WATER_DO_GPIO_PIN;			// 配置连接 传感器DO 的单片机引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 设置为上拉输入
		
		GPIO_Init(WATER_DO_GPIO_PORT, &GPIO_InitStructure);				// 初始化 
		
	}
	#endif
	
}

#if MODE
uint16_t WATER_ADC_Read(void)
{
	//设置指定ADC的规则组通道，采样时间
	return ADC_GetValue(ADC_CHANNEL, ADC_SampleTime_55Cycles5);
}
#endif

uint16_t WATER_GetData(void)
{
	
	#if MODE
	uint32_t  tempData = 0;
	for (uint8_t i = 0; i < WATER_READ_TIMES; i++)
	{
		tempData += WATER_ADC_Read();
		delay_ms(5);
	}

	tempData /= WATER_READ_TIMES;
	return tempData;
	
	#else
	uint16_t tempData;
	tempData = GPIO_ReadInputDataBit(WATER_DO_GPIO_PORT, WATER_DO_GPIO_PIN);
	return tempData;
	#endif
}



