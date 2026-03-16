/*******************************************************************************
 * File: dht11.h
 * Author: zonesion
 * Description: DHT11 driver header file
 * Updated: 2026-03-16 support PA5 pin
 * Notes:
 *   - Support single-wire communication protocol
 *   - Provide temperature and humidity reading interface
 *******************************************************************************/

#ifndef __DHT11_H__
#define __DHT11_H__

#include "stm32f10x.h"

/* DHT11 pin definition */
#define DHT11_GPIO_PORT       GPIOA
#define DHT11_GPIO_PIN        GPIO_Pin_5
#define DHT11_RCC_CLOCK       RCC_APB2Periph_GPIOA

/* Return code definition */
#define DHT11_OK              0
#define DHT11_ERROR           -1

/* Function prototypes */
float dht11_read_temp(void);
float dht11_read_humidity(void);
int dht11_init(void);

#endif /* __DHT11_H__ */
