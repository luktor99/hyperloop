/*
 * Serafin Bachman
 * line_encoder.h
 *
 *  Created on: 12.07.2017
 *      Author: ------
 */

#ifndef SHARED_DRIVERS_LINE_ENCODER_H_
#define SHARED_DRIVERS_LINE_ENCODER_H_

void PWM_Init(uint16_t value);
void ADC_unit3i4_Init();
float lowPassFrequency(float input, float previous);
uint32_t ReadBufforPaski();


#endif /* SHARED_DRIVERS_LINE_ENCODER_H_ */
