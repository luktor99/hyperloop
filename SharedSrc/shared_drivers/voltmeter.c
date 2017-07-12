/**
 * @file voltmeter.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 12-July-2017
 * @brief This file contains the implementation of the 12V rail voltage sensing driver
 */

#include "stm32f10x.h"
#include "voltmeter.h"
#include "hyper_unit_defs.h"

#define R1 10000	/**< Value of the R1 resistor in the voltage divider */
#define R2 3300		/**< Value of the R2 resistor in the voltage divider */

/**
 * @brief This function initializes peripherals required to read the ADC channel
 */
void Voltmeter_Init(void) {
	// ADC1 should be enabled by now

	// Set up the GPIO
	RCC_APB2PeriphClockCmd(UNIT_12VRAIL_RCC, ENABLE);
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_AIN;
	gpio_init.GPIO_Pin = UNIT_12VRAIL_PIN;
	GPIO_Init(UNIT_12VRAIL_GPIO, &gpio_init);
}

/**
 * @brief This function performs a single conversion of the ADC channel connected to 12V rail voltage divider
 * @return Voltage reading in 0..255 range (eg. 89 = 8.9V)
 */
uint8_t Voltmeter_Read(void) {
	ADC_RegularChannelConfig(ADC1, UNIT_12VRAIL_ADC_CH, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
	uint16_t adc_result = ADC_GetConversionValue(ADC1);
	return adc_result * 33 * (R1+R2) / R2 / 4095;
}
