/*******************************************************************************
 * File: water_sensor.c
 * Author: zonesion
 * Description: Water level sensor driver
 * Updated: 2026-03-16 support PA4 pin
 *******************************************************************************/

#include "water_sensor.h"

/* ADC initialization */
static void water_adc_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    /* Enable ADC1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* ADC initialization */
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* ADC calibration */
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

/* Read water level data */
uint16_t water_sensor_get_data(void)
{
    uint16_t value = 0;

    /* Configure ADC channel */
    ADC_RegularChannelConfig(ADC1, WATER_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);

    /* Start ADC conversion */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    /* Wait for conversion to complete */
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    /* Read conversion result */
    value = ADC_GetConversionValue(ADC1);

    return value;
}

/* Initialization function */
int water_sensor_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Initialize ADC */
    water_adc_init();

    /* Configure PA4 as analog input */
    GPIO_InitStructure.GPIO_Pin = WATER_ADC_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(WATER_ADC_PORT, &GPIO_InitStructure);

    return 0;
}
