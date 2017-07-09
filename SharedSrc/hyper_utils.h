/**
 * @file hyper_utils.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 4-July-2017
 * @brief This file contains headers of various utility functions
 */

#ifndef HYPER_UTILS_H_
#define HYPER_UTILS_H_

#include <stdint.h>
#include <stdbool.h>

void HYPER_SysTick_Init(void);
void HYPER_LED_Init(void);
void HYPER_TempSensor_Init(void);

void HYPER_Tick(void);
void HYPER_Delay(uint32_t duration_ms);
uint32_t HYPER_Delay_GetTime(void);
bool HYPER_Delay_Check(uint32_t start_time, uint32_t duration_ms);
void HYPER_LED_Tick(void);
void HYPER_LED_UpdateOK(void);

int16_t HYPER_TempSensor_Read(void);
void HYPER_TempSensor_Check(void);

#endif /* HYPER_UTILS_H_ */
