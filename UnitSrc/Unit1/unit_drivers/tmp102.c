/**
 * @file tmp102.c
 * @author Wojciech Bytof
 * @date 18-July-2017
 * @brief This file contains the implementation of tmp102 sensor
 */
 
 
#include "stm32f10x.h"
#include "tmp102.h"

#define tmp102_ADDR (0x48 << 1) /**< tmp102's I2C address */

/**
 * @brief Initialization of peripherals
 */
void tmp102_Init(void) 
{
	// RCC setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

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
	I2C_InitStruct.I2C_ClockSpeed = 400000;
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
 * @brief This function sets conversion frequency from default 4Hz to 8Hz (max)
 */
void tmp102_Config(void)
{
	// Make sure the bus is ready
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send tmp102's I2C address
	I2C_Send7bitAddress(I2C1, (tmp102_ADDR), I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// Enter Configuration Register(0b00000001)
	I2C_SendData(I2C1, 0x01);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Send MSB of Configuration Register (0b01100000)
	I2C_SendData(I2C1, 0x60);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Send LSB of Configuration Register (0b11100000)
	I2C_SendData(I2C1, 0xE0);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);
  }

/**
 * @brief This function reads a single 12-bit value from the device's register
 * @return Temperature in Celsius
 */
uint8_t tmp102_ReadTemp()
{
	//local variables
	uint8_t temp8bit = 0x00;
	uint16_t data = 0x0000;
	float subRemainder = 0;
	float tempCelsius;

	// Make sure the bus is ready
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send tmp102's I2C address
	I2C_Send7bitAddress(I2C1, (tmp102_ADDR), I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// Enter Temperature Register(0b00000000)
	I2C_SendData(I2C1, 0x00);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);


	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send tmp102's I2C address
	I2C_Send7bitAddress(I2C1, (tmp102_ADDR), I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	// Receive the data byte 1 (MSB)
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	data = I2C_ReceiveData(I2C1) << 4;

	// Receive the data byte 2 (LSB)
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	data |= I2C_ReceiveData(I2C1) >> 4;

	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);

	tempCelsius = data *0.0625;
	subRemainder = tempCelsius - (int)tempCelsius;

	if(subRemainder >= 0.5)
	{
		temp8bit = ((int)tempCelsius + 1);
		return temp8bit;
	}
	else
	{
		temp8bit = (int)tempCelsius;
		return temp8bit;
	}

}

   
