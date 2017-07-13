/**
 * @file Unit6/unit_main.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 4-July-2017
 * @brief This file contains implementation of the main functions (UNIT_Init() and UNIT_Loop()), which are specific to each of the units.
 */

#include "unit.h"
#include "hyper.h"
#include "unit_can.h"
#include "shared_drivers/brakes.h"
#include "unit_drivers/power.h"

/**
 * @brief This function performs initialization of the peripherals specific to the unit.
 */
void UNIT_Init(void) {
	Brakes_Init();
	Power_Init();
}

/**
 * @brief This function is run in an infinite loop. This is where outgoing data gets updated.
 */
inline void UNIT_Loop(void) {
	// TODO: Fill me.
}

/**
 * @brief This function processes a received CAN message
 * @param msg_type The message type @see MsgType_t
 */
void UNIT_CAN_ProcessFrame(MsgType_t msg_type) {
	if(msg_type == MSG_BRAKESHOLD)
		Brakes_Hold();
	else if(msg_type == MSG_BRAKESRELEASE)
		Brakes_Release();
	else if(msg_type == MSG_POWERDOWN)
		Power_Down();
}
