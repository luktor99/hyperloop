/**
 * @file tmp102.h
 * @author Wojciech Bytof
 * @date 13-July-2017
 * @brief This file contains the headers of tmp102 driver
 */

#ifndef UNIT_DRIVERS_TMP102_H_
#define UNIT_DRIVERS_TMP102_H_

void tmp102_Init(void);
void tmp102_Config(void);
uint8_t tmp102_ReadTemp();

#endif /* UNIT_DRIVERS_TMP102_H_ */
