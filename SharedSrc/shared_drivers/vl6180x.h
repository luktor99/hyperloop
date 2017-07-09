/**
 * @file vl6180x.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 6-July-2017
 * @brief This file contains the headers of VL6180X sensor driver
 */

#ifndef SHARED_DRIVERS_VL6180X_H_
#define SHARED_DRIVERS_VL6180X_H_

#include <stdbool.h>

#define VL6180X_ID1		(0x1 << 1)	/**< The ID of the 1st sensor (also its I2C address) */
#define VL6180X_ID2		(0x2 << 1)	/**< The ID of the 2nd sensor (also its I2C address) */
#define VL6180X_ID3		(0x3 << 1)	/**< The ID of the 3rd sensor (also its I2C address) */
#define VL6180X_ID4		(0x4 << 1)	/**< The ID of the 4th sensor (also its I2C address) */

void VL6180X_Init(void);
void VL6180X_InitSensor(uint8_t sensor_id);
bool VL6180X_IsSampleReady(uint8_t sensor_id);
uint8_t VL6180X_GetRange(uint8_t sensor_id);

#endif /* SHARED_DRIVERS_VL6180X_H_ */
