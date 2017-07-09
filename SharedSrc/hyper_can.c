/**
 * @file hyper_can.c
 * @author Łukasz Kilaszewski (luktor99)
 * @date 26-June-2017
 * @brief This file contains a set of functions that take care of the data transfers
 * between the units and the central node (Raspberry Pi) through the CAN bus.
 */

#include "stm32f10x.h"
#include "hyper_unit_defs.h"
#include "hyper_can.h"
#include "hyper_can_frames.h"
#include "hyper_settings.h"
#include "hyper_utils.h"

/**
 * @brief Structure that buffers this unit's CAN data messages
 */
static unit_DataBuffer_t unitDataBuffer = {0};

/**
 * @brief This function initializes the CAN1 peripheral and the required GPIOs.
 * The CAN message ID filter and CAN1_RX_IRQ get enabled as well.
 */
void HYPER_CAN_Init(void) {
	// Clocks setup
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	CAN_DeInit(CAN1);

	// CAN1 GPIOs setup
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Pin = GPIO_Pin_11; // PA11 - CANRX
	gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio_init);
	gpio_init.GPIO_Pin = GPIO_Pin_12; // PA12 - CANTX
	gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio_init);

	// CAN1 interface setup
	CAN_InitTypeDef can_init;
	CAN_StructInit(&can_init);
	can_init.CAN_RFLM = ENABLE;
	can_init.CAN_TXFP = DISABLE;
	can_init.CAN_Mode = CAN_Mode_Normal;
	can_init.CAN_SJW = CAN_SJW_1tq;
	can_init.CAN_BS1 = CAN_BS1_10tq;
	can_init.CAN_BS2 = CAN_BS2_7tq;
	can_init.CAN_Prescaler = HYPER_CAN_SPEED;
	CAN_Init(CAN1, &can_init);

	// CAN1 filter setup - only accept RTR messages with ID equal to UNIT_CAN_ID_DATA
	CAN_FilterInitTypeDef can_filter_init;
	can_filter_init.CAN_FilterNumber = 0;
	can_filter_init.CAN_FilterMode = CAN_FilterMode_IdList;
	can_filter_init.CAN_FilterScale = CAN_FilterScale_16bit;
	can_filter_init.CAN_FilterIdHigh = (UNIT_CAN_ID_DATA_OUT << 5) | (1 << 4);
	can_filter_init.CAN_FilterIdLow = 0x0;
	can_filter_init.CAN_FilterFIFOAssignment = CAN_FIFO0;
	can_filter_init.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&can_filter_init);

	// CAN1_RX interrupt setup
	NVIC_InitTypeDef nvic_init;
	nvic_init.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_init.NVIC_IRQChannelSubPriority = 0;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init);
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);

	// CAN status LED setup
	RCC_APB2PeriphClockCmd(UNIT_LED_RCC, ENABLE);
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin = UNIT_LED_PIN;
	gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(UNIT_LED_GPIO, &gpio_init);
}

/**
 * @brief This function prepares a data message and sends it through the CAN bus
 * @param id Message ID
 * @param data_length The amount of data bytes to be sent (0..8)
 * @param data_ptr Pointer to the data buffer
 */
static void HYPER_CAN_SendData(const uint32_t id, const uint8_t data_length, const uint8_t* data_ptr) {
	// Prepare the message
	CanTxMsg msg;
	msg.StdId = id;
	msg.IDE = CAN_Id_Standard;
	msg.RTR = CAN_RTR_Data;
	msg.DLC = data_length;
	for (uint8_t i = 0; i < data_length; i++)
		msg.Data[i] = data_ptr[i];
	// Transfer the message, block program execution while no mailbox is empty
	while (CAN_Transmit(CAN1, &msg) == CAN_TxStatus_NoMailBox);
}

/**
 * @brief This function processes a received CAN message and sets the corresponding flags
 * @param msg Pointer to the received message held in a CanRxMsg structure
 */
static void HYPER_CAN_ProcessFrame(CanRxMsg* msg) {
	// FIXME: random stuff here for now
	HYPER_CAN_SendData(UNIT_CAN_ID_DATA_OUT, sizeof(unitDataBuffer), (uint8_t *)&unitDataBuffer);
	// Update the status LED
	HYPER_LED_UpdateOK();
}

/**
 * @brief This function handles CAN1_RX0_IRQ.
 */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0)) {
		// Receive the message into a buffer
		CanRxMsg msg;
		CAN_Receive(CAN1, CAN_FIFO0, &msg);
		// Take appropriate action
		HYPER_CAN_ProcessFrame(&msg);
	}
}

/**
 * @brief This function performs a safe update of the CAN data buffer
 * @param update_func Pointer to the update function
 * @param value_ptr Pointer to the new value
 */
void HYPER_CAN_Update(void (*update_func)(unit_DataBuffer_t *, void *), void *value_ptr) {
	__disable_irq();
	update_func(&unitDataBuffer, value_ptr);
	__enable_irq();
}
