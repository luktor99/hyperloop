/**
 * @file hyper.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 26-June-2017
 * @brief This file contains common initialization functions.
 */

#include "hyper.h"

/**
 * @brief This function initializes all peripherals and interfaces necessary for every unit
 */
void HYPER_Init(void) {
	HYPER_SysTick_Init();
	HYPER_TempSensor_Init();
	HYPER_LED_Init();
	HYPER_CAN_Init();
}
