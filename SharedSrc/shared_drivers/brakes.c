/**
 * @file brakes.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 13-July-2017
 * @brief This file contains the implementation of the brakes driver
 */

#if defined(UNIT_2) || defined(UNIT_6) // Only compile this file for these units

#include "stm32f10x.h"
#include "brakes.h"
#include "hyper_can.h"
#include "hyper_unit_defs.h"
#include "hyper_utils.h"

#if defined(UNIT_2)
#define DEFAULT_STATE	BRAKES_NORMAL	/**< The default brakes state for UNIT_2 */
#elif defined(UNIT_6)
#define DEFAULT_STATE	BRAKES_POWEROFF	/**< The default brakes state for UNIT_6 */
#endif

#define GPIO_NORMAL		GPIO_Pin_0		/**< The GPIO pin connected to the BRAKES_N button */
#define GPIO_HOLD		GPIO_Pin_2		/**< The GPIO pin connected to the BRAKES_1 button */
#define GPIO_RELEASE	GPIO_Pin_1		/**< The GPIO pin connected to the BRAKES_0 button */

#define ON(x) GPIO_ReadInputDataBit(GPIOB, x)

/**
 * @brief This enum represents the possible states of the braking system
 */
typedef enum {
	BRAKES_POWEROFF = 0,
	BRAKES_NORMAL,
	BRAKES_HOLD,
	BRAKES_RELEASE
} BrakesState_t;

/**
 * @brief This variable holds the current state of the braking system
 */
static BrakesState_t brakesState = BRAKES_POWEROFF;

static void Brakes_SetState(BrakesState_t state);
void updateBrakes(unit_DataBuffer_t *buffer, void *value); // function from unit_can.h

/**
 * @brief This function initializes peripherals required to drive the brakes
 */
void Brakes_Init(void) {
	// GPIO setup
	RCC_APB2PeriphClockCmd(UNIT_BRAKES_RCC, ENABLE);
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin = UNIT_BRAKES_PIN_A | UNIT_BRAKES_PIN_B | UNIT_BRAKES_PIN_C;
	gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(UNIT_BRAKES_GPIO, &gpio_init);

	// Disable JTAG on unit 2
#if defined(UNIT_2)
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
#endif

	// Set the default brakes state
	Brakes_SetState(DEFAULT_STATE);

#if defined(UNIT_6) // Setup brakes manual control buttons in unit 6
	// Setup the GPIOs required for manual controls in UNIT_6
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Pin = GPIO_NORMAL | GPIO_HOLD | GPIO_RELEASE;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &gpio);

	HYPER_Delay(200);

	// Interrupts setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	NVIC_InitTypeDef nvic_init;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init.NVIC_IRQChannelSubPriority = 0;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;
	nvic_init.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_Init(&nvic_init);
	nvic_init.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init(&nvic_init);
	nvic_init.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init(&nvic_init);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);

	EXTI_InitTypeDef exti_init;
	exti_init.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2;
	exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger = EXTI_Trigger_Rising;
	exti_init.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_init);
#endif
}

/**
 * @brief This function commands the braking system to brake
 */
void Brakes_Hold(void) {
	Brakes_SetState(BRAKES_HOLD);
}

/**
 * @brief This function commands the braking system to release the brakes
 */
void Brakes_Release(void) {
	Brakes_SetState(BRAKES_RELEASE);
}

/**
 * @brief This function commands the braking system to idle (for driving and pumping)
 */
void Brakes_Normal(void) {
	Brakes_SetState(BRAKES_NORMAL);
}

/**
 * @brief This function powers off all the coils which control the brakes
 */
void Brakes_PowerOff(void) {
	Brakes_SetState(BRAKES_POWEROFF);
}

/**
 * @brief This function sets the braking system to the desired state
 * @param state The desired state @see BrakesState_t
 */
static void Brakes_SetState(BrakesState_t state) {
	// Update the state in the CAN buffer
	uint8_t can_brakes_state = (state == BRAKES_HOLD);
	HYPER_CAN_Update(updateBrakes, &can_brakes_state);

	// Output the new state
	if(state == BRAKES_NORMAL)
		UNIT_BRAKES_GPIO->BSRR = UNIT_BRAKES_PIN_A | UNIT_BRAKES_PIN_B | (UNIT_BRAKES_PIN_C << 16U); // A-HIGH, B-HIGH, C-LOW
	else if(state == BRAKES_HOLD || state == BRAKES_POWEROFF)
		UNIT_BRAKES_GPIO->BSRR = (UNIT_BRAKES_PIN_A << 16U) | (UNIT_BRAKES_PIN_B << 16U)| (UNIT_BRAKES_PIN_C << 16U); // A-LOW, B-LOW, C-LOW
	else if(state == BRAKES_RELEASE)
		UNIT_BRAKES_GPIO->BSRR = (UNIT_BRAKES_PIN_A << 16U) | (UNIT_BRAKES_PIN_B << 16U) | UNIT_BRAKES_PIN_C; // A-LOW, B-LOW, C-HIGH

	// Update the internal state
	brakesState = state;
}

#if defined(UNIT_6)

uint8_t Power_Check(void); // function from unit6's power driver

/**
 * @brief This function polls the manual brakes controls and takes appropriate actions
 */
void Buttons_Tick(void) {
	// If the system is powered on, take no action
	if(Power_Check())
		return;

	// Power is down, so taking action is allowed
	if(ON(GPIO_NORMAL) + ON(GPIO_HOLD) + ON(GPIO_RELEASE) > 1)
		return;
	else if(ON(GPIO_NORMAL) && brakesState != BRAKES_NORMAL)
		Brakes_Normal();
	else if(ON(GPIO_HOLD) && brakesState != BRAKES_HOLD)
		Brakes_Hold();
	else if(ON(GPIO_RELEASE) && brakesState != BRAKES_RELEASE)
		Brakes_Release();
}

/**
 * @brief This function handles the EXTI0_IRQ
 */
void EXTI0_IRQHandler(void) {
	Buttons_Tick();
	EXTI_ClearITPendingBit(EXTI_Line0);
}

/**
 * @brief This function handles the EXTI1_IRQ
 */
void EXTI1_IRQHandler(void) {
	Buttons_Tick();
	EXTI_ClearITPendingBit(EXTI_Line1);
}

/**
 * @brief This function handles the EXTI2_IRQ
 */
void EXTI2_IRQHandler(void) {
	Buttons_Tick();
	EXTI_ClearITPendingBit(EXTI_Line2);
}
#endif

#endif
