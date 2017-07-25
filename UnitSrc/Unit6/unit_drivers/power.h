/**
 * @file power.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 13-July-2017
 * @brief This file contains the headers of the system power driver
 */

#ifndef UNIT_DRIVERS_POWER_H_
#define UNIT_DRIVERS_POWER_H_

void Power_Init(void);
void Power_Down(void);
uint8_t Power_Check(void);

#endif /* UNIT_DRIVERS_POWER_H_ */
