
#ifndef _DRV_FAN_H_
#define _DRV_FAN_H_

#include <stdint.h>

/**
 * @brief	风扇驱动初始化
 * @param	None
 * @retval	None
 */
void FanInit(void);

/**
 * @brief	风扇状态控制
 * @param	None
 * @retval	None
 */
void FanCtrl(uint8_t cmd);

#endif /* _DRV_FAN_H_ */

