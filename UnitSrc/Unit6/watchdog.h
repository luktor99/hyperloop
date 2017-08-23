/**
 * @file watchdog.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 13-July-2017
 * @brief This file contains the implementation of the watchdog (unit 6)
 */

#ifndef UNITSRC_UNIT6_WATCHDOG_H_
#define UNITSRC_UNIT6_WATCHDOG_H_

#include <stdbool.h>
#include "hyper.h"
#include "hyper_settings.h"
#include "shared_drivers/brakes.h"
#include "unit_drivers/power.h"

/**
 * @brief The timestamp of the latest reset
 */
static uint32_t lastResetTimestamp;

/**
 * @brief The watchdog's state (ON/OFF)
 */
static bool watchdogON = false;

/**
 * @brief The timestamp of the latest lock update event
 */
static uint32_t lastLockTimestamp = 0;
/**
 * @brief The duration time of the latest brakes lock
 */
static uint16_t lockTime = 0;
/**
 * @brief Lock active flag
 */
static bool locked = false;

void Watchdog_Init(void);
void Watchdog_Tick(void);
void Watchdog_Reset(void);
static void Watchdog_Overflow(void);
bool Watchdog_IsLocked(void);
void Watchdog_Lock(uint16_t time_ms);

/**
 * @brief This function initializes the unit 6 watchdog
 */
void Watchdog_Init(void) {
	watchdogON = true;
	Watchdog_Reset();
}

/**
 * @brief This function takes appropriate actions if the watchdog has overflowed. It should be run as often as possible.
 */
void Watchdog_Tick(void) {
	if(locked) {
		if(HYPER_Delay_Check(lastLockTimestamp, lockTime)) {
			// Start / allow braking
			Brakes_PowerOff();

			// Disable the lock
			locked = 0;
		}
	}

	if(!watchdogON) {
		return;
	}

	// Take appropriate actions if overflow has occurred
	if(HYPER_Delay_Check(lastResetTimestamp, UNIT6_WATCHDOG_TIMEOUT))
		Watchdog_Overflow();
}

/**
 * @brief This function clears the watchdog timer, preventing the overflow from occurring
 */
void Watchdog_Reset(void) {
	// Update the timestamp
	lastResetTimestamp = HYPER_Delay_GetTime();
}

/**
 * @brief This function is called when the watchdog overflows
 */
static void Watchdog_Overflow(void) {
	// Enable the brakes
	if(Watchdog_IsLocked())
		Brakes_Hold();
	// Power down the rest of the system
	Power_Down();
	// Stop the watchdog
	watchdogON = false;
}

/**
 * This function checks if the brakes lock is currently active
 * @return Lock state (boolean)
 */
bool Watchdog_IsLocked(void) {
	return locked;
}

/**
 * This function locks the brakes for the given amount of time
 * @param time_ms Lock duration (in ms)
 */
void Watchdog_Lock(uint16_t time_ms) {
	//Brakes_Normal();
	lastLockTimestamp = HYPER_Delay_GetTime();
	lockTime = time_ms;
	locked = true;
}

#endif /* UNITSRC_UNIT6_WATCHDOG_H_ */
