/**
 * @file mlx90614.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 6-July-2017
 * @brief This file contains the implementation of MLX90614 sensor driver
 */

#if defined(UNIT_2) || defined(UNIT_5) // Only compile this file for these units

#include "stm32f10x.h"
#include "mlx90614.h"

#define MLX90614_ADDR (0x5A << 1) /**< MLX90614's I2C address */

#define TOBJ1 0x07 /**< TOBJ1 register's address */

static uint16_t MLX90614_ReadReg(uint8_t reg);

/**
 * @brief This function initializes the resources required to run the MLX90614 sensor
 */
void MLX90614_Init(void) {
	// RCC setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// TODO: enable sensor's power on Unit5

	// I2C1 SCL(PB6), SDA(PB7) pins setup
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_AF_OD;
	gpio_init.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio_init.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &gpio_init);

	// I2C1 setup
	I2C_DeInit(I2C1);
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2C_InitStruct);

	// Enable I2C1
	I2C_Cmd(I2C1, ENABLE);

	// Wait for I2C1 to become ready
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
}

/**
 * @brief This function reads a single 16-bit value from the device's register
 * @param reg Register's address
 * @return Register's value
 */
static uint16_t MLX90614_ReadReg(uint8_t reg) {
	// Make sure the bus is ready
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send MLX90614's I2C address
	I2C_Send7bitAddress(I2C1, MLX90614_ADDR, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// Send the register's address
	I2C_SendData(I2C1, reg);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send MLX90614's I2C address
	I2C_Send7bitAddress(I2C1, MLX90614_ADDR, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	// Disable ACK
	I2C_AcknowledgeConfig(I2C1, DISABLE);

	// Receive the data byte 1 (LSB)
	uint16_t data;
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data = I2C_ReceiveData(I2C1);
	// Receive the data byte 2 (MSB)
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	data |= I2C_ReceiveData(I2C1) << 8;

	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);

	// Enable ACK
	I2C_AcknowledgeConfig(I2C1, ENABLE);

	return data;
}

/**
 * @brief This function reads the temperature from the sensor.
 * @return Temperature expressed in °C (eg. 123 = 123°C) (Possible range: 0..255)
 */
uint8_t MLX90614_readTemp(void) {
	float temp = MLX90614_ReadReg(TOBJ1);
	temp *= 0.02f;
	temp -= 273.15f;

	if(temp >= 255.0f)
		return 255;
	else if(temp <= 0.0f)
		return 0;

	return (uint8_t)temp;
}

#endif
