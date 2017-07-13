/**
 * @file hyper_settings.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 4-July-2017
 * @brief This file contains settings of various parameters
 */

#ifndef HYPER_SETTINGS_H_
#define HYPER_SETTINGS_H_

#include "hyper_can.h"

#define HYPER_CAN_SPEED			HYPER_CAN_SPEED_1000KBPS	/**< CAN bus speed*/

#define HYPER_LED_BLINK_OK		1000 	/**< Status LED on-off time (in ms) when no error is detected */
#define HYPER_LED_BLINK_ERROR	100		/**< Status LED on-off time (in ms) when error is detected */

#define HYPER_INTERNAL_TEMP_MAX 	1100 	/**< Max temperature threshold in 0.1°C (eg. 1234 = 123.4°C). Exceeding this value causes a fatal error */
#define HYPER_INTERNAL_TEMP_PERIOD	500		/**< The time between internal temperature checks (in ms) */

#define UNIT6_WATCHDOG_TIMEOUT		1000	/**< The time it takes for the unit 6 watchdog to overflow */

#endif /* HYPER_SETTINGS_H_ */
