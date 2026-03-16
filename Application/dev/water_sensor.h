/*******************************************************************************
 * File: water_sensor.h
 * Author: zonesion
 * Description: Water level sensor driver header file
 * Updated: 2026-03-16 support PA4 pin (analog input)
 * Notes:
 *   - Use ADC to read analog signal
 *   - Provide data reading interface
 *******************************************************************************/

#ifndef __WATER_SENSOR_H__
#define __WATER_SENSOR_H__

#include "stm32f10x.h"

/* ADC related definition */
#define WATER_ADC_PORT        GPIOA
#define WATER_ADC_PIN         GPIO_Pin_4
#define WATER_ADC_RCC         (RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1)
#define WATER_ADC_CHANNEL     ADC_Channel_4  /* PA4 corresponds to ADC channel 4 */

/* Function prototypes */
uint16_t water_sensor_get_data(void);
int water_sensor_init(void);

#endif /* __WATER_SENSOR_H__ */
