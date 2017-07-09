/**
 * @file lm35.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 6-July-2017
 * @brief This file contains the headers of LM35 sensor driver
 */

#ifndef SHARED_DRIVERS_LM35_H_
#define SHARED_DRIVERS_LM35_H_

void LM35_Init(void);
uint16_t LM35_ReadADC(void);
uint16_t LM35_ReadTemp16(void);
uint8_t LM35_ReadTemp8(void);

#endif /* SHARED_DRIVERS_LM35_H_ */
