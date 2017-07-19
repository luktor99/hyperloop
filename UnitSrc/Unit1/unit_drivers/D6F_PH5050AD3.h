/**
 * @file tmp102.h
 * @author Wojciech Bytof
 * @date 13-July-2017
 * @brief This file contains the headers of tmp102 driver
 */

#ifndef UNIT_DRIVERS_D6F_PH5050AD3_H_
#define UNIT_DRIVERS_D6F_PH5050AD3_H_

void D6F_PH5050AD3_Init(void);
void D6F_PH5050AD3_Init_Message(void);
void D6F_PH5050AD3_StartAnotherRead(void);
uint16_t D6F_PH5050AD3_ReadPress();
float D6F_PH5050AD3_Conv_to_Pascal(uint16_t data);

#endif /* UNIT_DRIVERS_D6F_PH5050AD3_H_ */
