/**
 * @file Unit6/unit_can.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 5-July-2017
 * @brief This file contains implementation of functions that update the unit's CAN output buffer.
 */

#ifndef UNIT_CAN_H_
#define UNIT_CAN_H_

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateBrakes(unit_DataBuffer_t *buffer, void *value) {
	buffer->brakesState = *(uint8_t *)value;
}

#endif /* UNIT_CAN_H_ */
