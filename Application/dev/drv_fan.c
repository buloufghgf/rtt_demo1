
#include "stm32f10x.h"
#include <stdint.h>

/* 枚举风扇状态取值 */
typedef enum{
	FAL_VAL_ON  = 1,
	FAN_VAL_OFF = 0,
} FanVal_t;

/* 定义风扇配置结构体 */
typedef struct{
	/* PA引脚 */
	uint32_t		paClock;
	GPIO_TypeDef*	paPort;
	uint16_t		paPin;
	/* PB引脚 */
	uint32_t		pbClock;
	GPIO_TypeDef*	pbPort;
	uint16_t		pbPin;
} FanCfg_t;

static FanCfg_t g_fanCfg = {
	/* PA引脚 */
	RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_4,
	/* PB引脚 */
	RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_5,
};


/**
 * @brief	风扇驱动初始化
 * @param	None
 * @retval	None
 */
void FanInit(void)
{
	/* 开启GPIO端口时钟 */
	RCC_APB2PeriphClockCmd(g_fanCfg.paClock, ENABLE);
	RCC_APB2PeriphClockCmd(g_fanCfg.pbClock, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	/* 配置PA引脚功能 */
	GPIO_InitStructure.GPIO_Pin = g_fanCfg.paPin;
	GPIO_Init(g_fanCfg.paPort, &GPIO_InitStructure);
	
	/* 配置PB引脚功能 */
	GPIO_InitStructure.GPIO_Pin = g_fanCfg.pbPin;
	GPIO_Init(g_fanCfg.pbPort, &GPIO_InitStructure);
}

/**
 * @brief	风扇状态控制
 * @param	None
 * @retval	None
 */
void FanCtrl(uint8_t cmd)
{
	if(cmd == 1){
		/* 开启风扇 */
	    GPIO_SetBits(g_fanCfg.paPort, g_fanCfg.paPin);
    	GPIO_ResetBits(g_fanCfg.pbPort, g_fanCfg.pbPin);
	}
	else if(cmd == 0){
		/* 关闭风扇 */
		GPIO_ResetBits(g_fanCfg.paPort, g_fanCfg.paPin);
    	GPIO_ResetBits(g_fanCfg.pbPort, g_fanCfg.pbPin);
	}
}

