/**
 * @file hyper_can.h
 * @author £ukasz Kilaszewski (luktor99)
 * @date 26-June-2017
 * @brief This file contains the headers of the CAN bus related functions
 */

#ifndef HYPER_CAN_H_
#define HYPER_CAN_H_

#include "stdint.h"
#include "hyper_can_frames.h"

/**
 * @brief Possible CAN bus speed settings
 */
enum {
	HYPER_CAN_SPEED_1000KBPS = 2,
	HYPER_CAN_SPEED_500KBPS	= 4,
	HYPER_CAN_SPEED_250KBPS = 8
};

/**
 * @brief Structure type that buffers UNIT's CAN data messages
 */
#if defined UNIT_1
typedef unit1_DataBuffer_t unit_DataBuffer_t;
#elif defined UNIT_2
typedef unit2_DataBuffer_t unit_DataBuffer_t;
#elif defined UNIT_3
typedef unit3_DataBuffer_t unit_DataBuffer_t;
#elif defined UNIT_4
typedef unit4_DataBuffer_t unit_DataBuffer_t;
#elif defined UNIT_5
typedef unit5_DataBuffer_t unit_DataBuffer_t;
#elif defined UNIT_6
typedef unit6_DataBuffer_t unit_DataBuffer_t;
#endif

void HYPER_CAN_Init(void);
void HYPER_CAN_Update(void (*update_func)(unit_DataBuffer_t *, void *), void *value_ptr);

#endif /* HYPER_CAN_H_ */
