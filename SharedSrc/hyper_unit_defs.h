/**
 * @file hyper_unit_defs.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 26-June-2017
 * @brief This file contains the constants specific to each unit
 *
 * @attention
 * Unit selection is done by defining one of the constants during the compilation
 * process, by invoking gcc with -DUNIT_X parameter. The possible options are:
 * 		UNIT_1, UNIT_2, UNIT_3, UNIT_4,	UNIT_5,	UNIT_6
 */

#ifndef HYPER_UNIT_DEFS_H_
#define HYPER_UNIT_DEFS_H_

/**
 * @brief CAN bus message IDs definition
 */
#if defined UNIT_1
#define UNIT_CAN_ID_DATA_OUT		60	/**< The message ID for outgoing data requests and transfers */
#define UNIT_CAN_ID_DATA_IN			40	/**< The message ID for incoming data transfers */
#define UNIT_CAN_ID_ERROR			30	/**< The message ID for errors */
#elif defined UNIT_2
#define UNIT_CAN_ID_DATA_OUT		61	/**< The message ID for outgoing data requests and transfers */
#define UNIT_CAN_ID_DATA_IN			41	/**< The message ID for incoming data transfers */
#define UNIT_CAN_ID_ERROR			31	/**< The message ID for errors */
#elif defined UNIT_3
#define UNIT_CAN_ID_DATA_OUT		62	/**< The message ID for outgoing data requests and transfers */
#define UNIT_CAN_ID_DATA_IN			42	/**< The message ID for incoming data transfers */
#define UNIT_CAN_ID_ERROR			32	/**< The message ID for errors */
#elif defined UNIT_4
#define UNIT_CAN_ID_DATA_OUT		63	/**< The message ID for outgoing  data requests and transfers */
#define UNIT_CAN_ID_DATA_IN			43	/**< The message ID for incoming data transfers */
#define UNIT_CAN_ID_ERROR			33	/**< The message ID for errors */
#elif defined UNIT_5
#define UNIT_CAN_ID_DATA_OUT		64	/**< The message ID for outgoing  data requests and transfers */
#define UNIT_CAN_ID_DATA_IN			44	/**< The message ID for incoming data transfers */
#define UNIT_CAN_ID_ERROR			34	/**< The message ID for errors */
#elif defined UNIT_6
#define UNIT_CAN_ID_DATA_OUT		65	/**< The message ID for outgoing  data requests and transfers */
#define UNIT_CAN_ID_DATA_IN			45	/**< The message ID for incoming data transfers */
#define UNIT_CAN_ID_ERROR			35	/**< The message ID for errors */
#else
#error "Target unit undefined! Please define it before building (-DUNIT_X)."
#endif

/**
 * @brief Unit status LED pin definition
 */
#if defined UNIT_1
#define UNIT_LED_PIN			GPIO_Pin_8				/**< The GPIO pin the LED is connected to */
#define UNIT_LED_GPIO			GPIOB					/**< The GPIO peripheral the LED is connected to */
#define UNIT_LED_RCC			RCC_APB2Periph_GPIOB	/**< The RCC clock of the GPIO the LED is connected to */
#elif defined UNIT_2
#define UNIT_LED_PIN			GPIO_Pin_9				/**< The GPIO pin the LED is connected to */
#define UNIT_LED_GPIO			GPIOB					/**< The GPIO peripheral the LED is connected to */
#define UNIT_LED_RCC			RCC_APB2Periph_GPIOB	/**< The RCC clock of the GPIO the LED is connected to */
#elif defined UNIT_3
#define UNIT_LED_PIN			GPIO_Pin_8				/**< The GPIO pin the LED is connected to */
#define UNIT_LED_GPIO			GPIOA					/**< The GPIO peripheral the LED is connected to */
#define UNIT_LED_RCC			RCC_APB2Periph_GPIOA	/**< The RCC clock of the GPIO the LED is connected to */
#elif defined UNIT_4
#define UNIT_LED_PIN			GPIO_Pin_8				/**< The GPIO pin the LED is connected to */
#define UNIT_LED_GPIO			GPIOA					/**< The GPIO peripheral the LED is connected to */
#define UNIT_LED_RCC			RCC_APB2Periph_GPIOA	/**< The RCC clock of the GPIO the LED is connected to */
#elif defined UNIT_5
#define UNIT_LED_PIN			GPIO_Pin_8				/**< The GPIO pin the LED is connected to */
#define UNIT_LED_GPIO			GPIOB					/**< The GPIO peripheral the LED is connected to */
#define UNIT_LED_RCC			RCC_APB2Periph_GPIOB	/**< The RCC clock of the GPIO the LED is connected to */
#elif defined UNIT_6
#define UNIT_LED_PIN			GPIO_Pin_6				/**< The GPIO pin the LED is connected to */
#define UNIT_LED_GPIO			GPIOA					/**< The GPIO peripheral the LED is connected to */
#define UNIT_LED_RCC			RCC_APB2Periph_GPIOA	/**< The RCC clock of the GPIO the LED is connected to */
#endif

/**
 * @brief Internal temperature sensor coefficients
 */
#if defined UNIT_1
#define UNIT_TEMP_V_25_100			177450	/**< The V_25 value multiplied by 100 */
#define UNIT_TEMP_AVG_SLOPE_10		53		/**< The AVG_SLOPE value multiplied by 10 */
#define UNIT_TEMP_SHIFT				25		/**< The temperature shift (for calibration) */
#elif defined UNIT_2
#define UNIT_TEMP_V_25_100			177450	/**< The V_25 value multiplied by 100 */
#define UNIT_TEMP_AVG_SLOPE_10		53		/**< The AVG_SLOPE value multiplied by 10 */
#define UNIT_TEMP_SHIFT				25		/**< The temperature shift (for calibration) */
#elif defined UNIT_3
#define UNIT_TEMP_V_25_100			177450	/**< The V_25 value multiplied by 100 */
#define UNIT_TEMP_AVG_SLOPE_10		53		/**< The AVG_SLOPE value multiplied by 10 */
#define UNIT_TEMP_SHIFT				25		/**< The temperature shift (for calibration) */
#elif defined UNIT_4
#define UNIT_TEMP_V_25_100			177450	/**< The V_25 value multiplied by 100 */
#define UNIT_TEMP_AVG_SLOPE_10		53		/**< The AVG_SLOPE value multiplied by 10 */
#define UNIT_TEMP_SHIFT				25		/**< The temperature shift (for calibration) */
#elif defined UNIT_5
#define UNIT_TEMP_V_25_100			177450	/**< The V_25 value multiplied by 100 */
#define UNIT_TEMP_AVG_SLOPE_10		53		/**< The AVG_SLOPE value multiplied by 10 */
#define UNIT_TEMP_SHIFT				25		/**< The temperature shift (for calibration) */
#elif defined UNIT_6
#define UNIT_TEMP_V_25_100			177450	/**< The V_25 value multiplied by 100 */
#define UNIT_TEMP_AVG_SLOPE_10		53		/**< The AVG_SLOPE value multiplied by 10 */
#define UNIT_TEMP_SHIFT				25		/**< The temperature shift (for calibration) */
#endif

/**
 * @brief LM35 sensor connection
 */
#if defined UNIT_1
#define	UNIT_LM35_PIN			GPIO_Pin_3				/**< The GPIO pin the LM35 sensor is connected to */
#define UNIT_LM35_GPIO			GPIOA					/**< The GPIO peripheral the LM35 sensor is connected to */
#define UNIT_LM35_RCC			RCC_APB2Periph_GPIOA 	/**< The RCC clock of the GPIO the LM35 sensor is connected to */
#define UNIT_LM35_ADC_CH		ADC_Channel_3			/**< The ADC Channel the LM35 sensor is connected to */
#elif defined UNIT_2
#define	UNIT_LM35_PIN			GPIO_Pin_3				/**< The GPIO pin the LM35 sensor is connected to */
#define UNIT_LM35_GPIO			GPIOA					/**< The GPIO peripheral the LM35 sensor is connected to */
#define UNIT_LM35_RCC			RCC_APB2Periph_GPIOA 	/**< The RCC clock of the GPIO the LM35 sensor is connected to */
#define UNIT_LM35_ADC_CH		ADC_Channel_3			/**< The ADC Channel the LM35 sensor is connected to */
#endif

/**
 * @brief VL6180X sensor connections
 */
#if defined UNIT_1
#define UNIT_VL6180X_POWER_PIN		GPIO_Pin_12		/**< The GPIO pin thats controls the power-on MOSFET */
#define UNIT_VL6180X_POWER_GPIO		GPIOB			/**< The GPIO peripheral thats controls the power-on MOSFET */
#define UNIT_VL6180X_1_CE_PIN		GPIO_Pin_0		/**< The GPIO pin connected to 1st sensor's CE pin */
#define UNIT_VL6180X_1_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 1st sensor's CE pin */
#define UNIT_VL6180X_1_INT_PIN		GPIO_Pin_1		/**< The GPIO pin connected to 1st sensor's INT pin */
#define UNIT_VL6180X_1_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 1st sensor's INT pin */
#define UNIT_VL6180X_2_CE_PIN		GPIO_Pin_5		/**< The GPIO pin connected to 2nd sensor's CE pin */
#define UNIT_VL6180X_2_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 2nd sensor's CE pin */
#define UNIT_VL6180X_2_INT_PIN		GPIO_Pin_4		/**< The GPIO pin connected to 2nd sensor's INT pin */
#define UNIT_VL6180X_2_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 2nd sensor's INT pin */
#define UNIT_VL6180X_3_CE_PIN		GPIO_Pin_6		/**< The GPIO pin connected to 3rd sensor's CE pin */
#define UNIT_VL6180X_3_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 3rd sensor's CE pin */
#define UNIT_VL6180X_3_INT_PIN		GPIO_Pin_7		/**< The GPIO pin connected to 3rd sensor's INT pin */
#define UNIT_VL6180X_3_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 3rd sensor's INT pin */
#define UNIT_VL6180X_4_CE_PIN		GPIO_Pin_14		/**< The GPIO pin connected to 4th sensor's CE pin */
#define UNIT_VL6180X_4_CE_GPIO		GPIOB			/**< The GPIO peripheral connected to 4th sensor's CE pin */
#define UNIT_VL6180X_4_INT_PIN		GPIO_Pin_13		/**< The GPIO pin connected to 4th sensor's INT pin */
#define UNIT_VL6180X_4_INT_GPIO		GPIOB			/**< The GPIO peripheral connected to 4th sensor's INT pin */
#elif defined UNIT_2
#define UNIT_VL6180X_POWER_PIN		GPIO_Pin_2		/**< The GPIO pin thats controls the power-on MOSFET */
#define UNIT_VL6180X_POWER_GPIO		GPIOB			/**< The GPIO peripheral thats controls the power-on MOSFET */
#define UNIT_VL6180X_1_CE_PIN		GPIO_Pin_1		/**< The GPIO pin connected to 1st sensor's CE pin */
#define UNIT_VL6180X_1_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 1st sensor's CE pin */
#define UNIT_VL6180X_1_INT_PIN		GPIO_Pin_0		/**< The GPIO pin connected to 1st sensor's INT pin */
#define UNIT_VL6180X_1_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 1st sensor's INT pin */
#define UNIT_VL6180X_2_CE_PIN		GPIO_Pin_5		/**< The GPIO pin connected to 2nd sensor's CE pin */
#define UNIT_VL6180X_2_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 2nd sensor's CE pin */
#define UNIT_VL6180X_2_INT_PIN		GPIO_Pin_4		/**< The GPIO pin connected to 2nd sensor's INT pin */
#define UNIT_VL6180X_2_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 2nd sensor's INT pin */
#define UNIT_VL6180X_3_CE_PIN		GPIO_Pin_6		/**< The GPIO pin connected to 3rd sensor's CE pin */
#define UNIT_VL6180X_3_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 3rd sensor's CE pin */
#define UNIT_VL6180X_3_INT_PIN		GPIO_Pin_7		/**< The GPIO pin connected to 3rd sensor's INT pin */
#define UNIT_VL6180X_3_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 3rd sensor's INT pin */
#define UNIT_VL6180X_4_CE_PIN		GPIO_Pin_0		/**< The GPIO pin connected to 4th sensor's CE pin */
#define UNIT_VL6180X_4_CE_GPIO		GPIOB			/**< The GPIO peripheral connected to 4th sensor's CE pin */
#define UNIT_VL6180X_4_INT_PIN		GPIO_Pin_1		/**< The GPIO pin connected to 4th sensor's INT pin */
#define UNIT_VL6180X_4_INT_GPIO		GPIOB			/**< The GPIO peripheral connected to 4th sensor's INT pin */
#elif defined UNIT_5
#define UNIT_VL6180X_POWER_PIN		GPIO_Pin_2		/**< The GPIO pin thats controls the power-on MOSFET */
#define UNIT_VL6180X_POWER_GPIO		GPIOB			/**< The GPIO peripheral thats controls the power-on MOSFET */
#define UNIT_VL6180X_1_CE_PIN		GPIO_Pin_1		/**< The GPIO pin connected to 1st sensor's CE pin */
#define UNIT_VL6180X_1_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 1st sensor's CE pin */
#define UNIT_VL6180X_1_INT_PIN		GPIO_Pin_0		/**< The GPIO pin connected to 1st sensor's INT pin */
#define UNIT_VL6180X_1_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 1st sensor's INT pin */
#define UNIT_VL6180X_2_CE_PIN		GPIO_Pin_5		/**< The GPIO pin connected to 2nd sensor's CE pin */
#define UNIT_VL6180X_2_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 2nd sensor's CE pin */
#define UNIT_VL6180X_2_INT_PIN		GPIO_Pin_4		/**< The GPIO pin connected to 2nd sensor's INT pin */
#define UNIT_VL6180X_2_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 2nd sensor's INT pin */
#define UNIT_VL6180X_3_CE_PIN		GPIO_Pin_0		/**< The GPIO pin connected to 3rd sensor's CE pin */
#define UNIT_VL6180X_3_CE_GPIO		GPIOB			/**< The GPIO peripheral connected to 3rd sensor's CE pin */
#define UNIT_VL6180X_3_INT_PIN		GPIO_Pin_1		/**< The GPIO pin connected to 3rd sensor's INT pin */
#define UNIT_VL6180X_3_INT_GPIO		GPIOB			/**< The GPIO peripheral connected to 3rd sensor's INT pin */
#define UNIT_VL6180X_4_CE_PIN		GPIO_Pin_8		/**< The GPIO pin connected to 4th sensor's CE pin */
#define UNIT_VL6180X_4_CE_GPIO		GPIOA			/**< The GPIO peripheral connected to 4th sensor's CE pin */
#define UNIT_VL6180X_4_INT_PIN		GPIO_Pin_6		/**< The GPIO pin connected to 4th sensor's INT pin */
#define UNIT_VL6180X_4_INT_GPIO		GPIOA			/**< The GPIO peripheral connected to 4th sensor's INT pin */
#endif

#endif /* HYPER_UNIT_DEFS_H_ */
