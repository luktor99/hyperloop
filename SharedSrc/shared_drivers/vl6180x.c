/**
 * @file vl6180x.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 6-July-2017
 * @brief This file contains the implementation of VL6180X sensor driver
 */

#if defined(UNIT_1) || defined(UNIT_2) || defined(UNIT_5) // Only compile this file for these units

#include "stm32f10x.h"
#include "vl6180x.h"
#include "hyper.h"
#include "hyper_unit_defs.h"

#define VL6180X_I2C		I2C2			/**< I2C peripheral used to communicate with VL6180X sensors */
#define VL6180X_ADDR	(0x29 << 1)		/**< VL6180X's default I2C address */

#define SYSTEM__INTERRUPT_CONFIG_GPIO			0x014	/**< SYSTEM__INTERRUPT_CONFIG_GPIO register address */
#define SYSTEM__INTERRUPT_CLEAR					0x015	/**< SYSTEM__INTERRUPT_CLEAR register address */
#define SYSRANGE__START							0x018	/**< SYSRANGE__START register address */
#define SYSRANGE__INTERMEASUREMENT_PERIOD		0x01B	/**< SYSRANGE__INTERMEASUREMENT_PERIOD register address */
#define SYSRANGE__MAX_CONVERGENCE_TIME			0x01C	/**< SYSRANGE__MAX_CONVERGENCE_TIME register address */
#define SYSRANGE__VHV_RECALIBRATE				0x02E	/**< SYSRANGE__VHV_RECALIBRATE register address */
#define SYSRANGE__VHV_REPEAT_RATE				0x031	/**< SYSRANGE__VHV_REPEAT_RATE register address */
#define RESULT__INTERRUPT_STATUS_GPIO			0x04F	/**< RESULT__INTERRUPT_STATUS_GPIO register address */
#define RESULT__RANGE_VAL						0x062	/**< RESULT__RANGE_VAL register address */
#define READOUT__AVERAGING_SAMPLE_PERIOD		0x10A	/**< READOUT__AVERAGING_SAMPLE_PERIOD register address */
#define I2C_SLAVE__DEVICE_ADDRESS				0x212	/**< I2C_SLAVE__DEVICE_ADDRESS register address */

static uint8_t VL6180X_ReadReg(uint8_t i2c_address, uint16_t reg);
static void VL6180X_WriteReg(uint8_t i2c_address, uint16_t reg, uint8_t val);
static void VL6180X_SensorSetup(uint8_t sensor_id);
static void VL6180X_SensorSetAddress(uint8_t old_address, uint8_t new_address);
static void VL6180X_GPIO_CE_Init(GPIO_TypeDef *gpio, uint16_t pin);
static void VL6180X_GPIO_INT_Init(GPIO_TypeDef *gpio, uint16_t pin);

/**
 * @brief This function reads data from the sensor's register
 * @param i2c_address I2C address of the sensor
 * @param reg Register's address
 * @return Register value
 */
static uint8_t VL6180X_ReadReg(uint8_t i2c_address, uint16_t reg) {
	// Make sure the bus is ready
	while(I2C_GetFlagStatus(VL6180X_I2C, I2C_FLAG_BUSY));

	// Generate START condition
	I2C_GenerateSTART(VL6180X_I2C, ENABLE);
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_MODE_SELECT));

	// Send VL6180X's I2C address
	I2C_Send7bitAddress(VL6180X_I2C, i2c_address, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// Send MSB of the register's address
	I2C_SendData(VL6180X_I2C, (uint8_t)(reg >> 8));
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	// Send LSB of the register's address
	I2C_SendData(VL6180X_I2C, (uint8_t)(reg & 0xFF));
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Generate START condition
	I2C_GenerateSTART(VL6180X_I2C, ENABLE);
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_MODE_SELECT));

	// Send VL6180X's I2C address
	I2C_Send7bitAddress(VL6180X_I2C, i2c_address, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	// Disable ACK
	I2C_AcknowledgeConfig(VL6180X_I2C, DISABLE);

	// Receive the data
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED));
	uint8_t data = I2C_ReceiveData(VL6180X_I2C);

	// Generate STOP condition
	I2C_GenerateSTOP(VL6180X_I2C, ENABLE);

	// Enable ACK
	I2C_AcknowledgeConfig(VL6180X_I2C, ENABLE);

	return data;
}

/**
 * @brief This function writes data to the sensor's register
 * @param i2c_address I2C address of the sensor
 * @param reg Register's address
 * @param val Value to be written
 */
static void VL6180X_WriteReg(uint8_t i2c_address, uint16_t reg, uint8_t val) {
	// Make sure the bus is ready
	while(I2C_GetFlagStatus(VL6180X_I2C, I2C_FLAG_BUSY));

	// Generate START condition
	I2C_GenerateSTART(VL6180X_I2C, ENABLE);
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_MODE_SELECT));

	// Send VL6180X's I2C address
	I2C_Send7bitAddress(VL6180X_I2C, i2c_address, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// Send MSB of the register's address
	I2C_SendData(VL6180X_I2C, (uint8_t)(reg >> 8));
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	// Send LSB of the register's address
	I2C_SendData(VL6180X_I2C, (uint8_t)(reg & 0xFF));
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	// Send the data
	I2C_SendData(VL6180X_I2C, val);
	while(!I2C_CheckEvent(VL6180X_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Generate STOP condition
	I2C_GenerateSTOP(VL6180X_I2C, ENABLE);
}

/**
 * @brief This function initializes resources used by all VL6180X sensors. It must be called before any VL6180X_InitSensor() call.
 */
void VL6180X_Init(void) {
	// RCC setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// CE and INT pins setup
	VL6180X_GPIO_CE_Init(UNIT_VL6180X_1_CE_GPIO, UNIT_VL6180X_1_CE_PIN);
	VL6180X_GPIO_CE_Init(UNIT_VL6180X_2_CE_GPIO, UNIT_VL6180X_2_CE_PIN);
	VL6180X_GPIO_CE_Init(UNIT_VL6180X_3_CE_GPIO, UNIT_VL6180X_3_CE_PIN);
	VL6180X_GPIO_CE_Init(UNIT_VL6180X_4_CE_GPIO, UNIT_VL6180X_4_CE_PIN);
	VL6180X_GPIO_INT_Init(UNIT_VL6180X_1_INT_GPIO, UNIT_VL6180X_1_INT_PIN);
	VL6180X_GPIO_INT_Init(UNIT_VL6180X_2_INT_GPIO, UNIT_VL6180X_2_INT_PIN);
	VL6180X_GPIO_INT_Init(UNIT_VL6180X_3_INT_GPIO, UNIT_VL6180X_3_INT_PIN);
	VL6180X_GPIO_INT_Init(UNIT_VL6180X_4_INT_GPIO, UNIT_VL6180X_4_INT_PIN);

	// Power-control GPIO setup
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin = UNIT_VL6180X_POWER_PIN;
	gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(UNIT_VL6180X_POWER_GPIO, &gpio_init);

	// Reset all the VL6180X sensors by disabling powering them down for 100ms
	UNIT_VL6180X_POWER_GPIO->BSRR = UNIT_VL6180X_POWER_PIN; // Power OFF
	HYPER_Delay(100);
	UNIT_VL6180X_POWER_GPIO->BRR = UNIT_VL6180X_POWER_PIN; // Power ON

	// Wait for the sensors to power up again
	HYPER_Delay(100);

	// I2C2 SCL(PB10), SDA(PB11) pins setup
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	// I2C setup
	I2C_DeInit(VL6180X_I2C);
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(VL6180X_I2C, &I2C_InitStruct);

	// Enable I2C
	I2C_Cmd(VL6180X_I2C, ENABLE);

	// Wait for I2C to become ready
	while(I2C_GetFlagStatus(VL6180X_I2C, I2C_FLAG_BUSY));
}

/**
 * @brief This function initializes selected VL6180X sensor. VL6180X_Init() must be called once before calling this function.
 * @param sensor_id Sensor's ID (VL6180X_ID1, VL6180X_ID2, VL6180X_ID3, VL6180X_ID4)
 */
void VL6180X_InitSensor(uint8_t sensor_id) {
	if(sensor_id == VL6180X_ID1) {
		// Enable sensor by letting CE go HIGH
		UNIT_VL6180X_1_CE_GPIO->BSRR = UNIT_VL6180X_1_CE_PIN;
	}
	else if(sensor_id == VL6180X_ID2) {
		// Enable sensor by letting CE go HIGH
		UNIT_VL6180X_2_CE_GPIO->BSRR = UNIT_VL6180X_2_CE_PIN;
	}
	else if(sensor_id == VL6180X_ID3) {
		// Enable sensor by letting CE go HIGH
		UNIT_VL6180X_3_CE_GPIO->BSRR = UNIT_VL6180X_3_CE_PIN;
	}
	else if(sensor_id == VL6180X_ID4) {
		// Enable sensor by letting CE go HIGH
		UNIT_VL6180X_4_CE_GPIO->BSRR = UNIT_VL6180X_4_CE_PIN;
	}

	// Wait for the sensor to become available
	HYPER_Delay(80);

	// Setup the sensor (it has the default address right now)
	VL6180X_SensorSetup(VL6180X_ADDR);

	// Set sensor's I2C address to the target value
	VL6180X_SensorSetAddress(VL6180X_ADDR, sensor_id >> 1);
}

/**
 * @brief This function initializes selected sensor's registers to the desired values
 * @param sensor_id ID of the selected sensor
 */
static void VL6180X_SensorSetup(uint8_t sensor_id) {
	// Required - SR03 settings from application note AN4545
	VL6180X_WriteReg(sensor_id, 0x0207, 0x01);
	VL6180X_WriteReg(sensor_id, 0x0208, 0x01);
	VL6180X_WriteReg(sensor_id, 0x0096, 0x00);
	VL6180X_WriteReg(sensor_id, 0x0097, 0xfd);
	VL6180X_WriteReg(sensor_id, 0x00e3, 0x00);
	VL6180X_WriteReg(sensor_id, 0x00e4, 0x04);
	VL6180X_WriteReg(sensor_id, 0x00e5, 0x02);
	VL6180X_WriteReg(sensor_id, 0x00e6, 0x01);
	VL6180X_WriteReg(sensor_id, 0x00e7, 0x03);
	VL6180X_WriteReg(sensor_id, 0x00f5, 0x02);
	VL6180X_WriteReg(sensor_id, 0x00d9, 0x05);
	VL6180X_WriteReg(sensor_id, 0x00db, 0xce);
	VL6180X_WriteReg(sensor_id, 0x00dc, 0x03);
	VL6180X_WriteReg(sensor_id, 0x00dd, 0xf8);
	VL6180X_WriteReg(sensor_id, 0x009f, 0x00);
	VL6180X_WriteReg(sensor_id, 0x00a3, 0x3c);
	VL6180X_WriteReg(sensor_id, 0x00b7, 0x00);
	VL6180X_WriteReg(sensor_id, 0x00bb, 0x3c);
	VL6180X_WriteReg(sensor_id, 0x00b2, 0x09);
	VL6180X_WriteReg(sensor_id, 0x00ca, 0x09);
	VL6180X_WriteReg(sensor_id, 0x0198, 0x01);
	VL6180X_WriteReg(sensor_id, 0x01b0, 0x17);
	VL6180X_WriteReg(sensor_id, 0x01ad, 0x00);
	VL6180X_WriteReg(sensor_id, 0x00ff, 0x05);
	VL6180X_WriteReg(sensor_id, 0x0100, 0x05);
	VL6180X_WriteReg(sensor_id, 0x0199, 0x05);
	VL6180X_WriteReg(sensor_id, 0x01a6, 0x1b);
	VL6180X_WriteReg(sensor_id, 0x01ac, 0x3e);
	VL6180X_WriteReg(sensor_id, 0x01a7, 0x1f);
	VL6180X_WriteReg(sensor_id, 0x0030, 0x00);

	// Recommended / optional settings:
	VL6180X_WriteReg(sensor_id, READOUT__AVERAGING_SAMPLE_PERIOD, 0x0); // No averaging
	VL6180X_WriteReg(sensor_id, SYSRANGE__VHV_REPEAT_RATE, 0xFF); // Number of range measurements after which auto calibration of system is performed
	VL6180X_WriteReg(sensor_id, SYSRANGE__VHV_RECALIBRATE, 0x01); // perform a single temperature calibration of the ranging sensor
	VL6180X_WriteReg(sensor_id, SYSRANGE__INTERMEASUREMENT_PERIOD, 0x0); // Time delay between measurements in Ranging continuous mode (0 -> 10ms)
	VL6180X_WriteReg(sensor_id, SYSRANGE__MAX_CONVERGENCE_TIME, 0x4); // 4ms
	VL6180X_WriteReg(sensor_id, SYSTEM__INTERRUPT_CONFIG_GPIO, 0x04); // Interrupt source: new range sample ready

	// Start continuous mode
	VL6180X_WriteReg(sensor_id, SYSRANGE__START, 0x03);
}

/**
 * @brief This function updates the sensor's I2C address
 * @param old_address The current I2C address of the device
 * @param new_address The new I2C address of the device
 */
static void VL6180X_SensorSetAddress(uint8_t old_address, uint8_t new_address) {
	VL6180X_WriteReg(old_address, I2C_SLAVE__DEVICE_ADDRESS, new_address);
}

/**
 * @brief This function checks if there's a new sample ready to be read from the sensor
 * @param sensor_id Sensor's ID (VL6180X_ID1, VL6180X_ID2, VL6180X_ID3, VL6180X_ID4)
 * @return True / false
 */
bool VL6180X_IsSampleReady(uint8_t sensor_id) {
	return (VL6180X_ReadReg(sensor_id, RESULT__INTERRUPT_STATUS_GPIO) == 0x04);
}

/**
 * @brief This functions acquires a single distance sample from the sensor.
 * @param sensor_id Sensor's ID (VL6180X_ID1, VL6180X_ID2, VL6180X_ID3, VL6180X_ID4)
 * @return Range in mm
 */
uint8_t VL6180X_GetRange(uint8_t sensor_id) {
	uint8_t range = VL6180X_ReadReg(sensor_id, RESULT__RANGE_VAL);
	VL6180X_WriteReg(sensor_id, SYSTEM__INTERRUPT_CLEAR, 0x07);

	return range;
}

/**
 * @brief This function setups the given pin as an open-drain output and sets it LOW
 * @param gpio GPIOx peripheral
 * @param pin GPIO pin
 */
static void VL6180X_GPIO_CE_Init(GPIO_TypeDef *gpio, uint16_t pin) {
	// Setup CE as OD output
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_OD;
	gpio_init.GPIO_Pin = pin;
	gpio_init.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(gpio, &gpio_init);
	// Set the pin LOW
	gpio->BRR = pin;
}

/**
 * @brief This function setups the given pin as a floating input
 * @param gpio GPIOx peripheral
 * @param pin GPIO pin
 */
static void VL6180X_GPIO_INT_Init(GPIO_TypeDef *gpio, uint16_t pin) {
	// Setup INT as floating input (unused)
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_init.GPIO_Pin = pin;
	gpio_init.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(gpio, &gpio_init);
}

#endif
