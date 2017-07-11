/**
 * @file max6675.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 7-July-2017
 * @brief This file contains the headers of MAX6675 driver
 */

#ifndef UNIT_DRIVERS_MAX6675_H_
#define UNIT_DRIVERS_MAX6675_H_

void MAX6675_Init(void);
uint8_t MAX6675_ReadTemp(void);

#endif /* UNIT_DRIVERS_MAX6675_H_ */
