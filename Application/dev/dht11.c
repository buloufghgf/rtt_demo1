/*******************************************************************************
 * File: dht11.c
 * Author: zonesion
 * Description: DHT11 driver implementation
 * Updated: 2026-03-16 support PA5 pin
 *******************************************************************************/

#include "dht11.h"
#include <stdint.h>

/* Microsecond delay (using simple loop) */
static void dht11_delay_us(uint32_t us)
{
    volatile uint32_t i;
    for (; us > 0; us--)
        for (i = 0; i < 10; i++);
}

/* Set pin to output mode */
static void dht11_set_pin_output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
}

/* Set pin to input mode */
static void dht11_set_pin_input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
}

/* Start signal */
static uint8_t dht11_start(void)
{
    uint8_t retry = 0;

    /* Host pull low for at least 18ms */
    dht11_set_pin_output();
    GPIO_ResetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
    dht11_delay_us(2000);  /* about 2ms */

    /* Host pull high 20-40us */
    GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
    dht11_delay_us(30);

    /* Switch to input, read slave response */
    dht11_set_pin_input();

    /* Wait for slave to pull low */
    retry = 0;
    while (GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN))
    {
        retry++;
        if (retry > 100) return 1;  /* Timeout */
        dht11_delay_us(1);
    }

    /* Wait for slave to pull high */
    retry = 0;
    while (!GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN))
    {
        retry++;
        if (retry > 100) return 1;
        dht11_delay_us(1);
    }

    return 0;
}

/* Read one bit */
static uint8_t dht11_read_bit(void)
{
    uint8_t cnt = 0;

    /* Wait for low level end */
    while (!GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN))
    {
        cnt++;
        if (cnt > 100) return 0;
        dht11_delay_us(1);
    }

    /* Measure high level duration */
    cnt = 0;
    while (GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN))
    {
        cnt++;
        if (cnt > 100) return 0;
        dht11_delay_us(1);
    }

    /* High level duration > 30us means 1, otherwise 0 */
    return (cnt > 30) ? 1 : 0;
}

/* Read one byte */
static uint8_t dht11_read_byte(void)
{
    uint8_t i, byte = 0;
    for (i = 0; i < 8; i++)
    {
        byte <<= 1;
        byte |= dht11_read_bit();
    }
    return byte;
}

/* Read temperature */
float dht11_read_temp(void)
{
    uint8_t buffer[5];
    uint8_t i;
    float temp;

    if (dht11_start() != 0)
        return -100.0f;  /* Communication failed */

    for (i = 0; i < 5; i++)
    {
        buffer[i] = dht11_read_byte();
    }

    /* Checksum */
    if (buffer[4] != ((buffer[0] + buffer[1] + buffer[2] + buffer[3]) & 0xFF))
        return -100.0f;  /* Checksum failed */

    temp = (buffer[2] * 256 + buffer[3]) / 10.0f;
    return temp;
}

/* Read humidity */
float dht11_read_humidity(void)
{
    uint8_t buffer[5];
    uint8_t i;
    float humi;

    if (dht11_start() != 0)
        return -100.0f;  /* Communication failed */

    for (i = 0; i < 5; i++)
    {
        buffer[i] = dht11_read_byte();
    }

    /* Checksum */
    if (buffer[4] != ((buffer[0] + buffer[1] + buffer[2] + buffer[3]) & 0xFF))
        return -100.0f;  /* Checksum failed */

    humi = (buffer[0] * 256 + buffer[1]) / 10.0f;
    return humi;
}

/* Initialize DHT11 */
int dht11_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable clock */
    RCC_APB2PeriphClockCmd(DHT11_RCC_CLOCK, ENABLE);

    /* Configure PA5 as push-pull output and pull high */
    GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);

    /* Delay 1 second for DHT11 to stabilize */
    dht11_delay_us(1000000);

    return 0;
}
