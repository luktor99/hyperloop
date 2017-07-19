/**
 * @file current_sensor.h
 * @author Łukasz Kilaszewski (luktor99)
 * @author Serafin Bachman
 * @date 19-July-2017
 * @brief This file contains the headers of the current sensor driver
 */

#ifndef UNIT_DRIVERS_CURRENT_SENSOR_H_
#define UNIT_DRIVERS_CURRENT_SENSOR_H_

#include <stdint.h>

void CurrentSensor_Init(void);
uint8_t CurrentSensor_Read(void);

#endif /* UNIT_DRIVERS_CURRENT_SENSOR_H_ */
