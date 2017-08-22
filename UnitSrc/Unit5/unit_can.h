/**
 * @file Unit5/unit_can.h
 * @author Ĺ�ukasz Kilaszewski (luktor99)
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
void updateVL6180X_1(unit_DataBuffer_t *buffer, void *value) {
	buffer->vl6180xDistance1 = *(uint8_t *)value;
}

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateVL6180X_2(unit_DataBuffer_t *buffer, void *value) {
	buffer->vl6180xDistance2 = *(uint8_t *)value;
}

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateVL6180X_3(unit_DataBuffer_t *buffer, void *value) {
	buffer->vl6180xDistance3 = *(uint8_t *)value;
}

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateVL6180X_4(unit_DataBuffer_t *buffer, void *value) {
	buffer->vl6180xDistance4 = *(uint8_t *)value;
}

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updatePyro(unit_DataBuffer_t *buffer, void *value) {
	buffer->pyroTemperature = *(uint8_t *)value;
}


/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateVoltage12V(unit_DataBuffer_t *buffer, void *value) {
	buffer->voltage12V = *(uint8_t *)value;
}

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateCurrent(unit_DataBuffer_t *buffer, void *value) {
	buffer->current = *(uint8_t *)value;
}

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateBatteryVoltage(unit_DataBuffer_t *buffer, void *value) {
	buffer->voltageBattery = *(uint8_t *)value;\
}

#endif /* UNIT_CAN_H_ */
