/**
 * @file linear_encoder.c
 * @author Serafin Bachman
 * @date 19-July-2017
 * @brief This file contains the implementation of the linear encoder driver
 */

#include "stm32f10x.h"
#include "linear_encoder.h"

#define Mos1_Pin	GPIO_Pin_1		/**< The GPIO pin connected to the diode voltage level mosfet input */
#define Mos2_Pin	GPIO_Pin_2		/**< The GPIO pin connected to the diode voltage level mosfet input */
#define Mos3_Pin	GPIO_Pin_3		/**< The GPIO pin connected to the diode voltage level mosfet input */
#define ADC1_Pin	GPIO_Pin_4		/**< The GPIO pin connected to the line encoder ch1 input */
#define ADC2_Pin	GPIO_Pin_5		/**< The GPIO pin connected to the line encoder ch2 input */
#define ADC3_Pin	GPIO_Pin_0		/**< The GPIO pin connected to the line encoder ch3 input */

#define CUTOFF		10000			/**< Definition of cutoff frequency */
#define SAMPLE_RATE	25000 			/**< Definition of sampling rate (TRZEBA USTALIC) */
#define Threshold 	2000

static volatile uint16_t buforADC[3]={0}; // 16 musi byc

static float lowPassFrequency(float input, float previous);
static void PWM_Init(uint16_t value);
static void ADC_unit3i4_Init();

/**
 * @brief This function performs initialization of the peripherals required to drive the linear encoder
 */
void LinearEncoder_Init() {
	PWM_Init(500); // 1000 max
	ADC_unit3i4_Init();
}

/**
 * @brief This function performs initialization of TIM2 in PWM mode.
 */
static void PWM_Init(uint16_t value){
	/* TIM2 PWM */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = Mos1_Pin | Mos2_Pin | Mos3_Pin ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	 /* Timer configuration */
	TIM_TimeBaseInitTypeDef tim;
	TIM_OCInitTypeDef  channel;

	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler = 64 - 1;
	tim.TIM_Period = 1000 - 1;
	TIM_TimeBaseInit(TIM2, &tim);

	TIM_OCStructInit(&channel);
	channel.TIM_OCMode = TIM_OCMode_PWM2;
	channel.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM2, &channel);
	TIM_OC3Init(TIM2, &channel);
	TIM_OC4Init(TIM2, &channel);

	TIM_Cmd(TIM2, ENABLE);

	/* Mosfet voltage */
	TIM2->CCR2 = value;
	TIM2->CCR3 = value;
	TIM2->CCR4 = value;
}

/**
 * @brief This function performs initialization of ADC with DMA.
 */
static void ADC_unit3i4_Init(){
	/* ADC GPIO */
	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);   //wlacz taktowanie DMA
	//RCC_ADCCLKConfig(RCC_PCLK2_Div6); // taktowanie adc 64/6 = 10.6MHz max 14MHz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = ADC1_Pin | ADC2_Pin | ADC3_Pin ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* DMA configuration*/
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);                                                      // Usun ewentualna poprzednia konfiguracje DMA
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR; 				// Adres docelowy transferu
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&buforADC;            			// Adres poczatku bloku do przeslania
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                              // Kierunek transferu
	DMA_InitStructure.DMA_BufferSize = 3;                                           // Liczba elementow do przeslania (dlugosc bufora)
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                // Wylaczenie automatycznego zwiekszania adresu po stronie ADC
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                         // Wlaczenie automatycznego zwiekszania adresu po stronie pamieci (bufora)
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;     // Rozmiar pojedynczych przesylanych danych po stronie ADC (HalfWord = 16bit)
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;             // Rozmiar pojedynczych przesylanych danych po stronie pamieci (bufora)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                                 // Tryb dzialania kontrolera DMA - powtarzanie cykliczne
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                             // Priorytet DMA - wysoki
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                    // Wylaczenie obslugi transferu z pamieci do pamieci
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);                                    // Zapis konfiguracji

	/* ENABLE DMA, channel 1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);

	/* ADC configuration */
	ADC_InitTypeDef adc;
	ADC_StructInit(&adc);
	adc.ADC_ScanConvMode = ENABLE;
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_NbrOfChannel = 3;  //4
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_Init(ADC1, &adc);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 3, ADC_SampleTime_239Cycles5);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	/* NVIC configuration */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief This function performs low pass filter.
 */
static float lowPassFrequency(float input, float previous){

    float RC = 1.0/(CUTOFF*2*3.14);
    float dt = 1.0/SAMPLE_RATE;
    float alpha = dt/(RC+dt);
    float output = previous + (alpha*(input - previous));

    return output;
}

/**
 * @brief This function give number of detected straps
 */
uint32_t LinearEncoder_Read(){

	volatile uint32_t buforPaski = 0;
	volatile uint16_t napiecie[3]= {0};

	/* ADC values */
	int i;
	int wykryte=0;
	for ( i=0; i<3; i++ ) {
		napiecie[i] = lowPassFrequency(buforADC[i], napiecie[i]);
		if ( napiecie[i]> Threshold) wykryte++;
	}
	if(wykryte == 2) buforPaski++;
	return buforPaski;
}
