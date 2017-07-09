/**
 * @file hyper_utils.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 4-July-2017
 * @brief This file contains implementation of various utility functions
 */

#include "stm32f10x.h"
#include "hyper_utils.h"
#include "hyper_unit_defs.h"
#include "hyper_settings.h"

/**
 * @brief Milliseconds counter, incremented in SysTick_Handler() by calling HYPER_Tick();
 */
static volatile uint32_t sysTickCounter = 0;

/**
 * @brief Status LED state (OK - true / ERROR - false). Updated through HYPER_LED_UpdateOK()
 */
static uint32_t statusLEDStateOK = true;

/**
 * @brief This function initializes the SysTick counter, used as milliseconds counter for delays
 */
void HYPER_SysTick_Init(void) {
	// Initialize SysTick @ 1kHz
	if(SysTick_Config(SystemCoreClock / 1000))
		NVIC_SystemReset();
}

/**
 * @brief This function initializes the GPIO required to drive the status LED.
 */
void HYPER_LED_Init(void) {
	// Clock setup
	RCC_APB2PeriphClockCmd(UNIT_LED_RCC, ENABLE);
	// LED GPIO setup
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin = UNIT_LED_PIN;
	gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(UNIT_LED_GPIO, &gpio_init);
}

/**
 * @brief This function initializes the ADC circuitry required to read the internal temperature sensor.
 */
void HYPER_TempSensor_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitTypeDef adc_init;
	adc_init.ADC_Mode = ADC_Mode_Independent;
	adc_init.ADC_ScanConvMode = DISABLE;
	adc_init.ADC_ContinuousConvMode = DISABLE;
	adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc_init.ADC_DataAlign = ADC_DataAlign_Right;
	adc_init.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &adc_init);
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_Cmd(ADC1, ENABLE);
}

/**
 * @brief This function performs a single read of the temperature using the internal sensor.
 * @return Temperature expressed in 0.1°C (eg. 1234 = 123.4°C)
 */
int16_t HYPER_TempSensor_Read(void) {
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
	uint16_t adc_result = ADC_GetConversionValue(ADC1);
	return ((UNIT_TEMP_V_25_100 - adc_result * 100) / UNIT_TEMP_AVG_SLOPE_10) + UNIT_TEMP_SHIFT;
}

/**
 * @brief This function checks if the temperature measured by the microcontroller's internal sensor exceeds
 * the threshold value. In such case a fatal error is raised. The check is done every HYPER_INTERNAL_TEMP_PERIOD ms.
 */
void HYPER_TempSensor_Check(void) {
	static uint32_t delay_timestamp = 0;
	if(HYPER_Delay_Check(delay_timestamp, HYPER_INTERNAL_TEMP_PERIOD)) {
		if(HYPER_TempSensor_Read() > HYPER_INTERNAL_TEMP_MAX) {
			// Raise fatal error - temperature out of range
			//TODO: Fix me, temporary solution:
			for(;;);
		}

		// Delay the next check
		delay_timestamp = HYPER_Delay_GetTime();
	}
}

/**
 * @brief This function updates the time counter. Used by SysTick_Handler()
 */
void HYPER_Tick(void) {
	sysTickCounter++;
}

/**
 * @brief This functions blocks program execution for a given amount of time
 * @param duration_ms Delay duration in milliseconds
 */
void HYPER_Delay(uint32_t duration_ms) {
	uint32_t counter_start = sysTickCounter;
	while((sysTickCounter - counter_start) < duration_ms);
}

/**
 * @brief This function returns the current time stamp, required for non-blocking delays (done by HAL_Delay_Check())
 * @return Current time stamp (up time in milliseconds)
 */
uint32_t HYPER_Delay_GetTime(void) {
	return sysTickCounter;
}

/**
 * This function checks if a given delay has elapsed
 * @param start_time The delay start time (acquired through HYPER_Delay_GetTime())
 * @param duration_ms Delay duration in milliseconds
 * @return true if the delay has elapsed, false otherwise
 */
bool HYPER_Delay_Check(uint32_t start_time, uint32_t duration_ms) {
	return (sysTickCounter - start_time) >= duration_ms;
}

/**
 * @brief This functions updates the status LED. It should be run in the main loop.
 */
void HYPER_LED_Tick(void) {
	static bool led_state = false;
	static uint32_t delay_timestamp = 0;
	static uint32_t delay_duration = HYPER_LED_BLINK_OK;
	// Check if the desired delay has elapsed
	if(HYPER_Delay_Check(delay_timestamp, delay_duration)) {
		if(!led_state) {
			// Set status LED ON
			UNIT_LED_GPIO->BSRR = UNIT_LED_PIN;
		}
		else {
			// Set status LED OFF
			UNIT_LED_GPIO->BRR = UNIT_LED_PIN;
		}
		// Update the current LED state
		led_state = !led_state;

		// Decide the delay time (was there an ERROR?)
		if(statusLEDStateOK)
			delay_duration = HYPER_LED_BLINK_OK;
		else
			delay_duration = HYPER_LED_BLINK_ERROR;

		// Assume there will be an ERROR next time
		statusLEDStateOK = false;

		// Start the delay by updating the time stamp
		delay_timestamp = HYPER_Delay_GetTime();
	}
}

/**
 * @brief This function updates the status LED. Should be run at least every HYPER_LED_PERIOD_OK
 */
void HYPER_LED_UpdateOK(void) {
	statusLEDStateOK = true;
}
