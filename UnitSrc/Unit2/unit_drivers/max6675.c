/**
 * @file max6675.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 7-July-2017
 * @brief This file contains the implementation of MAX6675 driver
 */

#include "stm32f10x.h"
#include "max6675.h"

/**
 * @brief This function initializes resources required to drive the MAX6675 thermocouple interface
 */
void MAX6675_Init(void) {
	// RCC setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// GPIO setup (PB12 - NSS, PB13 - SCK, PB14 - MISO, PB15 - MOSI)
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Pin = GPIO_Pin_13;
	gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_init);
	gpio_init.GPIO_Pin = GPIO_Pin_14;
	gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &gpio_init);
	gpio_init.GPIO_Pin = GPIO_Pin_12;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &gpio_init);

	// Set NSS HIGH
	GPIOB->BSRR = GPIO_Pin_12;

	// SPI2 setup
	SPI_InitTypeDef spi_init;
	SPI_StructInit(&spi_init);
	spi_init.SPI_Mode = SPI_Mode_Master;
	spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi_init.SPI_DataSize = SPI_DataSize_16b;
	spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
	spi_init.SPI_NSS = SPI_NSS_Soft;
	spi_init.SPI_CPOL = SPI_CPOL_Low;
	spi_init.SPI_CPHA = SPI_CPHA_2Edge;
	spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; // 36 MHz / 16 = 2.25 MHz
	SPI_Init(SPI2, &spi_init);

	// Enable SPI2
	SPI_Cmd(SPI2, ENABLE);
}

/**
 * @brief This function performs a single reading of the temperature
 * @return Temperature expressed in °C (eg. 123 = 123°C) (Possible range: 0..255)
 */
uint8_t MAX6675_ReadTemp(void) {
	// Set NSS LOW
	GPIOB->BRR = GPIO_Pin_12;

	// Send dummy 16 bits
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, (uint16_t)0x0);
	// Get received data (16 bits)
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	uint16_t data = SPI_I2S_ReceiveData(SPI2);

	// Set NSS HIGH
	GPIOB->BSRR = GPIO_Pin_12;

	// Open thermocouple detection
	if(data & 0x4)
		return 0;

	// Retrieve temperature in 0..1023°C range
	uint16_t temp = (data >> 5) & 0x3FF;
	if(temp > 255)
		return 0;

	return temp;
}
