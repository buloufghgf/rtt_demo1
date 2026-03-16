
#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <stdint.h>

/* 节点类型宏定义 */
#define SENSOR_TYPE  500

/**
 * @brief	传感器初始化
 * @param	None
 * @param	None
 */
void SensorInit(void);

/**
 * @brief	传感器入网成功回调
 * @param	None
 * @param	None
 */
void SensorLinkOn(void);

/**
 * @brief	采集类传感器数据上报
 * @param	None
 * @param	None
 */
void SensorUpdate(void);

/**
 * @brief	安放类传感器数据监测
 * @param	None
 * @param	None
 */
void SensorCheck(void);

/**
 * @brief	控制类传感器指令控制
 * @param	cmd: 命令值
 * @param	None
 */
void SensorControl(uint8_t cmd);

/**
 * @brief	应用层指令处理
 * @param	ptag: 等号左边键，pval: 等号右边值，obuf: 指令处理结果
 * @param	>0指令处理结果返回数据长度，0：没有返回数据，<0：不支持指令
 */
int z_process_command_call(char* ptag, char* pval, char* obuf);

#endif /* _SENSOR_H_ */
