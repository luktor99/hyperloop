/**
 * @file Unit34/unit_main.c
 * @author Ĺ�ukasz Kilaszewski (luktor99)
 * @author Serafin Bachman
 * @date 4-July-2017
 * @brief This file contains implementation of the main functions (UNIT_Init() and UNIT_Loop()), which are specific to each of the units.
 */

#include "unit.h"
#include "hyper.h"
#include "unit_can.h"
#include "unit_drivers/angular_encoder.h"
#include "unit_drivers/linear_encoder.h"

/**
 * @brief This function performs initialization of the peripherals specific to the unit.
 */
void UNIT_Init(void) {
	LinearEncoder_Init();
	AngularEncoder_Init();
}

/**
 * @brief This function is run in an infinite loop. This is where outgoing data gets updated.
 */
inline void UNIT_Loop(void) {
	int32_t angular_enc = AngularEncoder_GetPos();
	HYPER_CAN_Update(updateEnkoder, &angular_enc);

	uint32_t linear_enc = LinearEncoder_Read();
	HYPER_CAN_Update(updatePaski, &linear_enc);
}
