/**
 * @file angular_encoder.c
 * @author Serafin Bachman
 * @date 19-July-2017
 * @brief This file contains the implementation of the angular encoder driver
 */

#include "stm32f10x.h"
#include "angular_encoder.h"

#define Enk_ch1		GPIO_Pin_6 		/**< The GPIO pin connected to the angular encoder ch1 input */
#define Enk_ch2		GPIO_Pin_7 		/**< The GPIO pin connected to the angular encoder ch2 input */

volatile uint16_t pulse_count = 0;
volatile uint32_t time =0;
volatile uint16_t velocity =0;

volatile int32_t enc_pos = 0;

/**
 * @brief This function performs initialization of TIM3 in enkoder mode.
 */
void AngularEncoder_Init() {
	/* Enkoder GPIO */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = Enk_ch1 | Enk_ch2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Timer configuration ENKODER MODE */
	TIM_DeInit(TIM3);  // Konfiguracja timera do zliczania impulsow z enkodera
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI1, TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);
	TIM3->ARR = 65535;
	TIM3->CR1 = TIM_CR1_UDIS;  // przeładowanie licznika
	TIM3->CCMR1 = (0x01 << 8) | (0x01 << 0);  // konfiguracja wejsc 1 i 2 odpowiednio na pinach TI1 i TI2

	TIM_Cmd(TIM3, ENABLE);

	/* NVIC configuration */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //najwyzszy priorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Set the counter to the middle position
	TIM3->CNT = 0;
}

/**
 * @brief This function performs TIM3 interupt after one full wheel cycle.
 */
volatile uint32_t time_new = 0;
volatile uint32_t time_old = 0;

void TIM3_IRQHandler() {

	time_new = SysTick->VAL;

	velocity = (40/(time_new - time_old))*1000;  // distance subtract by time difference

	time_old = time_new;
}

/**
 * @brief This function performs velocity.
 */
uint16_t AngularVelocity_Read() {
	/* Encoder counter */
	return velocity;
}

/**
 * @brief This function performs number of counted pulses.
 */
uint16_t AngularEnkoder_Read() {
	/* Encoder counter */
	pulse_count = TIM_GetCounter(TIM3);
	return pulse_count;
}

/**
 * This function returns the current absolute encoder position
 * @return Absolute encoder position (1024 ticks per revolution)
 */
int32_t AngularEncoder_GetPos() {
	int16_t delta;
	__disable_irq();
	delta = (int16_t)TIM3->CNT;
	TIM3->CNT = 0;
	__enable_irq();

	return enc_pos += delta;
}



