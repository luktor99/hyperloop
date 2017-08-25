/**
 * @file linear_encoder.c
 * @author Serafin Bachman
 * @date 19-July-2017
 * @brief This file contains the implementation of the linear encoder driver
 */

#include "stm32f10x.h"
#include "linear_encoder.h"
#include <stdbool.h>
#include "hyper_utils.h"

#define Mos1_Pin	GPIO_Pin_1		/**< The GPIO pin connected to the diode voltage level mosfet input */
#define Mos2_Pin	GPIO_Pin_2		/**< The GPIO pin connected to the diode voltage level mosfet input */
#define Mos3_Pin	GPIO_Pin_3		/**< The GPIO pin connected to the diode voltage level mosfet input */
#define ADC1_Pin	GPIO_Pin_4		/**< The GPIO pin connected to the line encoder ch1 input */
#define ADC2_Pin	GPIO_Pin_5		/**< The GPIO pin connected to the line encoder ch2 input */
#define ADC3_Pin	GPIO_Pin_0		/**< The GPIO pin connected to the line encoder ch3 input */

#define CUTOFF		1000			/**< Definition of cutoff frequency */
#define SAMPLE_RATE	25000 			/**< Definition of sampling rate (TRZEBA USTALIC) */
#define Threshold 	2000

#define MIN_THRESHOLD 8

static volatile uint16_t buforADC[3]={0};
uint32_t counter = 0;

static uint16_t calib = 0;
static uint16_t max = 0;

static volatile float value = 0.0f;

const float alpha = 0.001f;

static float lowPassFrequency(float input, float previous);
static void ADC_unit3i4_Init();

/**
 * @brief This function performs initialization of the peripherals required to drive the linear encoder
 */
void LinearEncoder_Init() {
	ADC_unit3i4_Init();

	// Calibrate the encoder
	HYPER_Delay(200);
	uint32_t acc = 0;
	for(uint16_t i = 0; i < 500; ++i) {
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
		acc += ADC_GetConversionValue(ADC1);
		HYPER_Delay(1);
	}

	calib = acc / 500;
	max = calib + MIN_THRESHOLD;
}

/**
 * @brief This function performs initialization of ADC with DMA.
 */
static void ADC_unit3i4_Init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = ADC1_Pin | ADC2_Pin | ADC3_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_InitTypeDef adc_init;
	adc_init.ADC_Mode = ADC_Mode_Independent;
	adc_init.ADC_ScanConvMode = DISABLE;
	adc_init.ADC_ContinuousConvMode = DISABLE;
	adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc_init.ADC_DataAlign = ADC_DataAlign_Right;
	adc_init.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &adc_init);
	ADC_Cmd(ADC1, ENABLE);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);
}

/**
 * @brief This function performs low pass filter.
 */
static float lowPassFrequency(float input, float previous){
    float output = previous + (alpha*(input - previous));

    return output;
}

/**
 * @brief This function give number of detected straps
 */
uint32_t LinearEncoder_Read() {
	static bool strip_detected = false;

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
	uint16_t adc_result = ADC_GetConversionValue(ADC1);
	buforADC[0] = adc_result;
	value = lowPassFrequency((float)adc_result, value);

	if(value > max)
		max = value;

	if(strip_detected) {
		if(value < calib+(max-calib)/3)
			strip_detected = false;
	}
	else {
		if(value > calib+(max-calib)*2/3) {
			strip_detected = true;
			++counter;
		}
	}

	return counter;
}
