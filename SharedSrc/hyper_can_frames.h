/**
 * @file hyper_can_frames.h
 * @author £ukasz Kilaszewski (luktor99)
 * @date 26-June-2017
 * @brief This file contains the CAN data frames definitions
 */

#ifndef HYPER_CAN_FRAMES_H_
#define HYPER_CAN_FRAMES_H_

/**
 * @brief Structure type that buffers UNIT1 CAN data messages
 */
typedef struct {
	uint8_t vl6180xDistance1	: 8;	/**< Distance reading from distance sensor 1 (VL6180X) */
	uint8_t vl6180xDistance2	: 8;	/**< Distance reading from distance sensor 2 (VL6180X) */
	uint8_t vl6180xDistance3	: 8;	/**< Distance reading from distance sensor 3 (VL6180X) */
	uint8_t vl6180xDistance4	: 8;	/**< Distance reading from distance sensor 4 (VL6180X) */
	int16_t pitotPressure		: 12;	/**< Pressure reading from the Pitot sensor */
	uint8_t lm35Temperature		: 8;	/**< Temperature reading from LM35 sensor */
	uint8_t tmp102Tmperature	: 8;	/**< Temperature reading from TMP-102 sensor */
} __attribute__((__packed__)) unit1_DataBuffer_t;

/**
 * @brief Structure type that buffers UNIT2 CAN data messages
 */
typedef struct {
	uint8_t vl6180xDistance1	: 8;	/**< Distance reading from distance sensor 1 (VL6180X) */
	uint8_t vl6180xDistance2	: 8;	/**< Distance reading from distance sensor 2 (VL6180X) */
	uint8_t vl6180xDistance3	: 8;	/**< Distance reading from distance sensor 3 (VL6180X) */
	uint8_t vl6180xDistance4	: 8;	/**< Distance reading from distance sensor 4 (VL6180X) */
	uint8_t pyroTemperature		: 8;	/**< Temperature reading from MLX90614 pyrometer */
	uint8_t lm35Temperature		: 7;	/**< Temperature reading from LM35 sensor */
	uint8_t brakesState			: 1;	/**< Brakes state */
	uint8_t tCoupleTemperature	: 8;	/**< Temperature reading from thermocouple (MAX6675) */
	uint8_t voltage12V			: 8;	/**< 12V rail voltage reading */
} __attribute__((__packed__)) unit2_DataBuffer_t;

/**
 * @brief Structure type that buffers UNIT3 CAN data messages
 */
typedef struct {
    uint32_t stripesCounter		: 32;	/**< Linear encoder value (stripes counter) */
    int16_t encoderVelocity		: 16;	/**< Encoder velocity */
} __attribute__((__packed__)) unit3_DataBuffer_t;

/**
 * @brief Structure type that buffers UNIT4 CAN data messages (same as for UNIT3)
 */
typedef unit3_DataBuffer_t unit4_DataBuffer_t;

/**
 * @brief Structure type that buffers UNIT5 CAN data messages
 */
typedef struct {
	uint8_t vl6180xDistance1	: 8;	/**< Distance reading from distance sensor 1 (VL6180X) */
	uint8_t vl6180xDistance2	: 8;	/**< Distance reading from distance sensor 2 (VL6180X) */
	uint8_t vl6180xDistance3	: 8;	/**< Distance reading from distance sensor 3 (VL6180X) */
	uint8_t vl6180xDistance4	: 8;	/**< Distance reading from distance sensor 4 (VL6180X) */
	uint8_t pyroTemperature		: 7;	/**< Temperature reading from MLX90614 pyrometer */

} __attribute__((__packed__)) unit5_DataBuffer_t;

/**
 * @brief Structure type that buffers UNIT6 CAN data messages
 */
typedef struct {
	uint8_t brakesState			: 1;	/**< Brakes state */
} __attribute__((__packed__)) unit6_DataBuffer_t;

#endif /* HYPER_CAN_FRAMES_H_ */
