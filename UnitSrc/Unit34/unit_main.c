/**
 * @file Unit34/unit_main.c
 * @author £ukasz Kilaszewski (luktor99), Serafin Bachman
 * @date 4-July-2017
 * @brief This file contains implementation of the main functions (UNIT_Init() and UNIT_Loop()), which are specific to each of the units.
 */

#include "unit.h"
#include "hyper.h"
#include "unit_can.h"
#include "shared_drivers/angular_encoder.h"
#include "shared_drivers/line_encoder.h"

/**
 * @brief This function performs initialization of the peripherals specific to the unit.
 */
void UNIT_Init(void) {
	// TODO: Fill me.
	PWM_Init(500); // 1000 max
	Enkoder_Init();
	ADC_unit3i4_Init();
}

/**
 * @brief This function is run in an infinite loop. This is where outgoing data gets updated.
 */
inline void UNIT_Loop(void) {
	// TODO: Fill me.

	/* Can implementation */
	uint16_t temprite = HYPER_TempSensor_Read();

	uint16_t pulse_counter = ReadAngularEnkoder();
	HYPER_CAN_Update(updateEnkoder, &pulse_counter);

	uint32_t buffor = ReadBufforPaski();
	HYPER_CAN_Update(updatePaski, &buffor);

}

