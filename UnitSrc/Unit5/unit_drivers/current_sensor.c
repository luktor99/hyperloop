/**
 * @file current_sensor.c
 * @author Łukasz Kilaszewski (luktor99)
 * @author Serafin Bachman
 * @date 19-July-2017
 * @brief This file contains the implementation of the current sensor driver
 */

#include "stm32f10x.h"
#include "current_sensor.h"

/**
 * @brief This function initializes peripherals required to read the current sensor
 */
void CurrentSensor_Init(void) {
	// ADC1 should be enabled by now

	// Set up the GPIO
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_AIN;
	gpio_init.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &gpio_init);
}

/**
 * @brief This function performs a single conversion of the ADC channel connected to the current sensor
 */
uint8_t CurrentSensor_Read(void) {
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);

    uint16_t current = (ADC_GetConversionValue(ADC1) - 3032)*33000/28/4095;
    if(current > 255)
    	return 255;
	return (uint8_t)current;
}
