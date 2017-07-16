/**
 * @file voltmeter.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 12-July-2017
 * @brief This file contains the headers of the 12V rail voltage sensing driver
 */

#ifndef SHARED_DRIVERS_VOLTMETER_H_
#define SHARED_DRIVERS_VOLTMETER_H_

void Current_Init(void);
uint8_t Current_Read(void);

void Pressure_Init(void);
uint8_t Pressure_Read(void);


#endif /* SHARED_DRIVERS_VOLTMETER_H_ */
