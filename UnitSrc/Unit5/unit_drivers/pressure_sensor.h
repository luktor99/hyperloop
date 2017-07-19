/**
 * @file pressure_sensor.h
 * @author Łukasz Kilaszewski (luktor99)
 * @author Serafin Bachman
 * @date 19-July-2017
 * @brief This file contains the headers of the pod pressure sensor driver
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include <stdint.h>

void PressureSensor_Init(void);
uint8_t PressureSensor_Read(void);

#endif /* PRESSURE_SENSOR_H_ */
