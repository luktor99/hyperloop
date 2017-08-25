/**
 * @file tmp102.c
 * @author Wojciech Bytof
 * @date 18-July-2017
 * @brief This file contains the implementation of D6F_PH5050AD3 sensor
 */
 
 
#include "stm32f10x.h"
#include "D6F_PH5050AD3.h"

#define AVG_LENGTH		20		/**< Length of the moving average filter */
#define VALUE_SCALE		650		/**< The scaling factor */

static uint16_t avg[AVG_LENGTH] = {0};
static uint8_t avg_i = 0;

#define D6F_PH5050AD3_ADDR (0x6C << 1) /**< tmp102's I2C address */

/**
 * @brief Initialization of peripherals
 */
void D6F_PH5050AD3_Init(void) 
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
 * @brief The device must be unlocked then write 0x00 to the EEPROM Control Register(0xB) to load NVM trim values, but keep the MCU in non-reset state.
 */
void D6F_PH5050AD3_Init_Message(void)
{
	// Make sure the bus is ready
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send D6F_PH5050AD3's I2C address
	I2C_Send7bitAddress(I2C1, (D6F_PH5050AD3_ADDR), I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	//EEPROM Control Register(0xB)
	I2C_SendData(I2C1, 0x0B);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//value send to Control Register
	I2C_SendData(I2C1, 0x00);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);
  }

/**
* @brief Function that starts another read-out
*/
void D6F_PH5050AD3_StartAnotherRead(void)
{
	// Make sure the bus is ready
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send D6F_PH5050AD3's I2C address
	I2C_Send7bitAddress(I2C1, (D6F_PH5050AD3_ADDR), I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// Access Address 1
 	I2C_SendData(I2C1, 0x00);
 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//MSB of Sensor Control Register
 	I2C_SendData(I2C1, 0xD0);
 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//LSB of Sensor Control Register
 	I2C_SendData(I2C1, 0x40);
 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//Serial Ctrl (16-bit adress, write, new request, 1 byte data transfer)
 	I2C_SendData(I2C1, 0x18);
 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//Data to write to Sensor Control Register
 	I2C_SendData(I2C1, 0x06);
 	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

 	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);
   }

/**
 * @brief Function performs a single read-out of pressure
 * @return bare data without processing
 */
uint16_t D6F_PH5050AD3_ReadPress(void)
{
	uint16_t data = 0x0000;
	// Make sure the bus is ready
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send D6F_PH5050AD3's I2C address
	I2C_Send7bitAddress(I2C1, (D6F_PH5050AD3_ADDR), I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// Access Address 1
	I2C_SendData(I2C1, 0x00);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//MSB of Compensated Flow rate Register
	I2C_SendData(I2C1, 0xD0);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//LSB of Compensated Flow rate Register
	I2C_SendData(I2C1, 0x51);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//2byte read
	I2C_SendData(I2C1, 0x2C);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);


	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send D6F_PH5050AD3's I2C address
	I2C_Send7bitAddress(I2C1, (D6F_PH5050AD3_ADDR), I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	//Read Buffer 0
	I2C_SendData(I2C1, 0x07);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	// Generate START condition
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	// Send D6F_PH5050AD3's I2C address
	I2C_Send7bitAddress(I2C1, (D6F_PH5050AD3_ADDR), I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_AcknowledgeConfig(I2C1, ENABLE);

	// Receive the data byte 1 (MSB)
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	data = I2C_ReceiveData(I2C1) << 8;

	I2C_AcknowledgeConfig(I2C1, DISABLE);

	// Receive the data byte 2 (LSB)
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	data |= I2C_ReceiveData(I2C1);

	// Generate STOP condition
	I2C_GenerateSTOP(I2C1, ENABLE);

	avg[avg_i] = data;
	avg_i = (avg_i + 1) % AVG_LENGTH;
	uint32_t sum = 0;
	for(uint8_t i = 0; i < AVG_LENGTH; i++) {
		sum += avg[i];
	}

	return sum*VALUE_SCALE/AVG_LENGTH;
}

/**
 * @brief Function performs conversion pressure to Pascals
 * @return pressure in Pascals
 */
float D6F_PH5050AD3_Conv_to_Pascal(uint16_t data)
{
	float pressure_Pascal = (((((float)data) - 1024)/60)-500);
	return pressure_Pascal;
}
