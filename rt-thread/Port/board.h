
#ifndef _BOARD_H_
#define _BOARD_H_

#include <rtthread.h>
#include <stdint.h>
#include "stm32f10x.h"

/* 开发板硬件初始化 */
void rt_hw_board_init(void);

/* 微秒延时函数 */
void rt_hw_udelay(rt_uint32_t us);

#endif
