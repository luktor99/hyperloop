/**
 * @file hyper_unit_defs.h
 * @author Ĺ�ukasz Kilaszewski (luktor99) & Serafin Bachman
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
#define UNIT_LED_GPIO			GPIOA					/**< The GPIO peripheral the LED is connected to */ ADC_Channel_0
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

/**
 * @brief 12V rail voltage measurement connection
 */
#if defined UNIT_2
#define	UNIT_12VRAIL_PIN			GPIO_Pin_2				/**< The GPIO pin the 12V rail voltage is connected to */
#define UNIT_12VRAIL_GPIO			GPIOA					/**< The GPIO peripheral the 12V rail voltage is connected to */
#define UNIT_12VRAIL_RCC			RCC_APB2Periph_GPIOA 	/**< The RCC clock of the GPIO the 12V rail voltage is connected to */
#define UNIT_12VRAIL_ADC_CH			ADC_Channel_2			/**< The ADC Channel the 12V rail voltage is connected to */
#elif defined UNIT_5
#define	UNIT_12VRAIL_PIN			GPIO_Pin_7				/**< The GPIO pin the 12V rail voltage is connected to */
#define UNIT_12VRAIL_GPIO			GPIOA					/**< The GPIO peripheral the 12V rail voltage is connected to */
#define UNIT_12VRAIL_RCC			RCC_APB2Periph_GPIOA 	/**< The RCC clock of the GPIO the 12V rail voltage is connected to */
#define UNIT_12VRAIL_ADC_CH			ADC_Channel_7			/**< The ADC Channel the 12V rail voltage is connected to */


#define ADC1_Pin GPIO_Pin_3
#define ADC2_Pin GPIO_Pin_4
#define ADC3_Pin GPIO_Pin_7
#define CUTOFF 10000								// Do ustalenia
#define SAMPLE_RATE 25000 							// Do ustalenia
#endif

/**
 * @brief Brakes interface
 */ ADC_Channel_0
#if defined UNIT_2
#define UNIT_BRAKES_GPIO			GPIOB					/**< The GPIO peripheral A, B, C inputs are connected to */
#define UNIT_BRAKES_RCC				RCC_APB2Periph_GPIOB	/**< The RCC clock of the GPIO */
#define UNIT_BRAKES_PIN_A			GPIO_Pin_3				/**< The GPIO pin connected to the A input */
#define UNIT_BRAKES_PIN_B			GPIO_Pin_4				/**< The GPIO pin connected to the B input */
#define UNIT_BRAKES_PIN_C			GPIO_Pin_5				/**< The GPIO pin connected to the C input */
#elif defined UNIT_6
#define UNIT_BRAKES_GPIO			GPIOA					/**< The GPIO peripheral A, B, C inputs are connected to */
#define UNIT_BRAKES_RCC				RCC_APB2Periph_GPIOA	/**< The RCC clock of the GPIO */
#define UNIT_BRAKES_PIN_A			GPIO_Pin_3				/**< The GPIO pin connected to the A input */
#define UNIT_BRAKES_PIN_B			GPIO_Pin_2				/**< The GPIO pin connected to the B input */
#define UNIT_BRAKES_PIN_C			GPIO_Pin_1				/**< The GPIO pin connected to the C input */
#endif

/**
 * @brief encoders connections
 */
#if defined UNIT_3 || UNIT_4
#define Enk_ch1 GPIO_Pin_6 									/**< The GPIO pin connected to the angular encoder ch1 input */
#define Enk_ch2 GPIO_Pin_7 									/**< The GPIO pin connected to the angular encoder ch2 input */
#define Mos1_Pin GPIO_Pin_1									/**< The GPIO pin connected to the diode voltage level mosfet input */
#define Mos2_Pin GPIO_Pin_2									/**< The GPIO pin connected to the diode voltage level mosfet input */
#define Mos3_Pin GPIO_Pin_3									/**< The GPIO pin connected to the diode voltage level mosfet input */
#define ADC1_Pin GPIO_Pin_4									/**< The GPIO pin connected to the line encoder ch1 input */
#define ADC2_Pin GPIO_Pin_5									/**< The GPIO pin connected to the line encoder ch2 input */
#define ADC3_Pin GPIO_Pin_0									/**< The GPIO pin connected to the line encoder ch3 input */

#define CUTOFF 10000										/**< Deffinition of cutoff frequency */
#define SAMPLE_RATE 25000 									/**< Deffinition of sampling rate (TRZEBA USTALIC) */

#endif

/**
 * @brief current and pressure ADC connections
 */
#if defined UNIT5
#define UNIT_CURRENT_Pin GPIO_Pin_4                         /**< The GPIO pin connected to the current sensor input */

#define UNIT_PRESSURE_PIN GPIO_Pin_5                        /**< The GPIO pin connected to the pod internal pressure input */

#endif

#endif /* HYPER_UNIT_DEFS_H_ */
