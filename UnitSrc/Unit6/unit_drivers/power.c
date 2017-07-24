/**
 * @file power.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 13-July-2017
 * @brief This file contains the implementation of the system power driver
 */

#include "stm32f10x.h"
#include "power.h"

/**
 * @brief This function initializes resources required to control the power
 */
void Power_Init(void) {
	// GPIO setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Pin = GPIO_Pin_10;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_init);

	// Set NOT_PE low
	GPIOB->BRR = GPIO_Pin_10;
}

/**
 * @brief This function powers down the system immediately
 */
void Power_Down(void) {
	// Set NOT_PE high
	GPIOB->BSRR = GPIO_Pin_10;
}
