/**
 * @file battery_voltage_sensor.h
 * @author Łukasz Kilaszewski (luktor99)
 * @author Serafin Bachman
 * @date 19-July-2017
 * @brief This file contains the headers of the pod Battery voltage sensor driver
 */

#ifndef Voltage_SENSOR_H_
#define Voltage_SENSOR_H_

#include <stdint.h>

void VoltageSensor_Init(void);
uint8_t VoltageSensor_Read(void);

#endif /* Voltage_SENSOR_H_ */
