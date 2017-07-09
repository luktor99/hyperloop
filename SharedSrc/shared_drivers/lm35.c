/**
 * @file lm35.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 6-July-2017
 * @brief This file contains the implementation of LM35 sensor driver
 */

#if defined(UNIT_1) || defined(UNIT_2) // Only compile this file for these units

#include "stm32f10x.h"
#include "lm35.h"
#include "hyper_unit_defs.h"

/**
 * @brief This function initializes peripherals required to drive the LM35 sensor
 */
void LM35_Init(void) {
	// ADC1 should be enabled by now

	// Set up the GPIO LM35 is connected to
	RCC_APB2PeriphClockCmd(UNIT_LM35_RCC, ENABLE);
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_AIN;
	gpio_init.GPIO_Pin = UNIT_LM35_PIN;
	GPIO_Init(UNIT_LM35_GPIO, &gpio_init);
}

/**
 * @brief This function performs a single conversion of the ADC channel the LM35 sensor is connected to
 * @return
 */
uint16_t LM35_ReadADC(void) {
	ADC_RegularChannelConfig(ADC1, UNIT_LM35_ADC_CH, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
	uint16_t adc_result = ADC_GetConversionValue(ADC1);
	return adc_result;
}

/**
 * @brief This function reads the temperature from LM35 sensor with high resolution
 * @return Temperature expressed in 0.1�C (eg. 1234 = 123.4�C)
 */
uint16_t LM35_ReadTemp16(void) {
	uint16_t adc_sample = LM35_ReadADC();
	// LM35 outputs 10mV/�C
	return adc_sample * 3300 / 4095;
}

/**
 * @brief This function reads the temperature from LM35 sensor with low resolution
 * @return Temperature expressed in �C (eg. 123 = 123�C) (Possible range: 0..255)
 */
uint8_t LM35_ReadTemp8(void) {
	uint16_t adc_sample = LM35_ReadADC();
	// LM35 outputs 10mV/�C
	uint16_t temp = adc_sample * 330 / 4095;
	if(temp > 255)
		return 255; // overflow

	return (uint8_t)temp;
}

#endif
