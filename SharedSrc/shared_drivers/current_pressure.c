/**
 * @file voltmeter.c
 * @author Łukasz Kilaszewski (luktor99) & Serafin Bachman
 * @date 12-July-2017
 * @brief This file contains the implementation of the 12V rail voltage sensing driver
 */

#if defined(UNIT_5) 

#include "stm32f10x.h"
#include "voltmeter.h"
#include "hyper_unit_defs.h"

/**
 * @brief This function initializes peripherals required to read the ADC channel
 */
void Current_Init(void) {
	// ADC1 should be enabled by now

	// Set up the GPIO
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_AIN;
	gpio_init.GPIO_Pin = UNIT_CURRENT_PIN;
	GPIO_Init(GPIOA, &gpio_init);
}

/**
 * @brief This function performs a single conversion of the ADC channel connected to current value
 */
uint8_t Current_Read(void) {
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_3, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
	
    uint16_t adc_result = ADC_GetConversionValue(ADC1);
	return adc_result;
}

/**
 * @brief This function initializes peripherals required to read the ADC channel
 */
void Pressure_Init(void) {
	// ADC1 should be enabled by now

	// Set up the GPIO
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_AIN;
	gpio_init.GPIO_Pin = UNIT_PRESSURE_PIN;
	GPIO_Init(GPIOA, &gpio_init);
}

/**
 * @brief This function performs a single conversion of the ADC channel connected to inside pod pressure value
 */
uint8_t Pressure_Read(void) {
	ADC_RegularChannelConfig(ADC1,  ADC_Channel_2 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
	
    uint16_t adc_result = ADC_GetConversionValue(ADC1);
	return adc_result;
}

#endif
