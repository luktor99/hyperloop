/**
 * @file Unit1/unit_can.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 5-July-2017
 * @brief This file contains implementation of functions that update the unit's CAN output buffer.
 */

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
void updatePitot(unit_DataBuffer_t *buffer, void *value) {
	buffer->pitotPressure = *(int16_t *)value;
}

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateLM35(unit_DataBuffer_t *buffer, void *value) {
	buffer->lm35Temperature = *(uint8_t *)value;
}

/**
 * @brief This function updates the CAN data buffer
 * @param buffer Pointer to the CAN buffer structure
 * @param value Pointer to the new data
 */
void updateTMP102(unit_DataBuffer_t *buffer, void *value) {
	buffer->tmp102Tmperature = *(uint8_t *)value;
}
