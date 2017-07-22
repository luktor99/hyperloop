/**
 * @file Unit1/unit_main.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 4-July-2017
 * @brief This file contains implementation of the main functions (UNIT_Init() and UNIT_Loop()), which are specific to each of the units.
 */

#include "unit.h"
#include "hyper.h"
#include "unit_can.h"
#include "shared_drivers/lm35.h"
#include "shared_drivers/vl6180x.h"
#include "unit_drivers/D6F_PH5050AD3.h"
#include "unit_drivers/tmp102.h"

/**
 * @brief This function performs initialization of the peripherals specific to the unit.
 */
void UNIT_Init(void) {
	LM35_Init();

	VL6180X_Init();
	VL6180X_InitSensor(VL6180X_ID1);
	VL6180X_InitSensor(VL6180X_ID2);
	VL6180X_InitSensor(VL6180X_ID3);
	VL6180X_InitSensor(VL6180X_ID4);

	tmp102_Init();
	tmp102_Config();
	D6F_PH5050AD3_Init_Message();
}

/**
 * @brief This function is run in an infinite loop. This is where outgoing data gets updated.
 */
inline void UNIT_Loop(void) {
	// Read and update VL6180X sensors if there are new samples available
	if(VL6180X_IsSampleReady(VL6180X_ID1)) {
		uint8_t range1 = VL6180X_GetRange(VL6180X_ID1);
		HYPER_CAN_Update(updateVL6180X_1, &range1);
	}
	if(VL6180X_IsSampleReady(VL6180X_ID2)) {
		uint8_t range2 = VL6180X_GetRange(VL6180X_ID2);
		HYPER_CAN_Update(updateVL6180X_2, &range2);
	}
	if(VL6180X_IsSampleReady(VL6180X_ID3)) {
		uint8_t range3 = VL6180X_GetRange(VL6180X_ID3);
		HYPER_CAN_Update(updateVL6180X_3, &range3);
	}
	if(VL6180X_IsSampleReady(VL6180X_ID4)) {
		uint8_t range4 = VL6180X_GetRange(VL6180X_ID4);
		HYPER_CAN_Update(updateVL6180X_4, &range4);
	}

	// Read and update the LM35 sensor
	uint8_t lm35_temp = LM35_ReadTemp8();
	HYPER_CAN_Update(updateLM35, &lm35_temp);

	//Read and update tmp102 sensor if there are new samples available
	static uint32_t temperature_timestamp = 0;
	if (HYPER_Delay_Check(temperature_timestamp, 125)) {
		uint8_t tmp102_Celsius = tmp102_ReadTemp();
		HYPER_CAN_Update(updateTMP102, &tmp102_Celsius);

		// Update the time stamp
		temperature_timestamp = HYPER_Delay_GetTime();
	}

	//Read and update D6F_PH5050AD3 sensor if there are new samples available
	static uint32_t pitot_timestamp = 0;
	if (HYPER_Delay_Check(pitot_timestamp, 40)) {
		uint16_t pitot_press = D6F_PH5050AD3_ReadPress();
		HYPER_CAN_Update(updatePitot, &pitot_press);
		//ask pitot to start another read-out
		D6F_PH5050AD3_StartAnotherRead();
		// Update the time stamp
		pitot_timestamp = HYPER_Delay_GetTime();
	}
}
