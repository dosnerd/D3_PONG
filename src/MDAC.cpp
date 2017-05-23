/**
  ******************************************************************************
  * @file    dac_sound.cpp
  * @author  Rick Kock
  * @version V1.0.0
  * @date    22-May-2017
  * @brief   Digital to Analog Converter implementation
  ******************************************************************************
  * @description
  * Contains DAC implementation concerning the STM32F407 micro-controller. It
  * is used to produce three sounds on the console whenever a collision has
  * occurred in the 3D-Pong game. (assuming the directory of this project is
  * misspelled. Otherwise, change it accordingly).
  ******************************************************************************
  */

#include "../inc/MDAC.h"
#include <Vector.h>
#include <stm32f4xx_conf.h>

MDAC MDAC::sInstance;

MDAC::MDAC() {
	GPIOinit();
	DACinit();
}

// TODO: finish initialization method
void MDAC::GPIOinit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	// Make sure pin is set to analog (GPIO pin A4 or A5)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;			// DAC 1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;		// Set to analog
	// GPIO_InitStructure.GPIO_OType = GPIO_OTy;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// DACoutput = Vref * DOR / 4096

// TODO: Read more about 'DMA underrun'
// Select noise generation.
void MDAC::DACinit() {


	 DAC_InitTypeDef DAC_InitStructure;

	 // Configure clock for DAC
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	 DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;	// Select max amplitude value.

	 // Enable DAC output buffer. (BOFFx bit in DAC_CR)
	 DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;						// Enable buffer.

	 // Set hardware trigger. If trigger occurs, transfer is performed three APB1 clock cycles later.
	 DAC_InitStructure.DAC_Trigger = DAC_Trigger_None; // DAC_Trigger_Ext_IT9;								// Select external pin interrupt.

	 // When selecting external trigger, a DMA request will be generated.

	 DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Noise;					// Select noise to product sinusoids.

	 DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	// Enable DAC channel which will connect to the DAC_OUTx
	DAC_Cmd(DAC_Channel_1, ENABLE);

	// Disable dual software triggered command
	DAC_DualSoftwareTriggerCmd(DISABLE);

	// Enable wave generation and set noise
	DAC_WaveGenerationCmd(DAC_Channel_1, DAC_Wave_Noise, ENABLE);


}

void MDAC::setData(uint16_t data) {
	DAC_SetChannel1Data(DAC_Align_12b_R, data);
}

uint16_t getChannel1Data(void) {
	return DAC_GetDataOutputValue(DAC_Channel_1);
}

MDAC *MDAC::getInstance() {
	return &sInstance;
}

MDAC::~MDAC() {}

/*  Function used to set the DAC configuration to the default reset state *****/
//void DAC_DeInit(void);
//
///*  DAC channels configuration: trigger, output buffer, data format functions */
//void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
//void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
//void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);
//void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
//void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
//void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);
//void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
//void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);
//void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
//uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);
//
///* DMA management functions ***************************************************/
//void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);
//
///* Interrupts and flags management functions **********************************/
//void DAC_ITConfig(uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState);
//FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG);
//void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG);
//ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT);
//void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT);

// TODO: create method: select trigger

// TODO: create method: select wave generation

// TODO: create method: select triangle amplitude

// TODO: create method: select DAC output buffer

// TODO: create method: select DAC channel

// TODO: create method: align DAC data

// TODO: create method:

// TODO: create method:

/**
 * ******************************************************************************
 * The DAC module is a 12-bit, voltage output digital-to-analog converter. It may
 * be used in conjunction with the DMA controller. For this project, we're going
 * to generate a noise wave.
 *
 * Digital to analog conversions allow computers to interact with analog signals.
 * ******************************************************************************
 */


/**
 * ******************************************************************************
 * The fundamental consideration in sampling is how fast to sample a signal to be
 * able to reconstruct it.
 *
 * The sampling frequency is the number of samples per second. This is to be
 * compared with the signal cyclic frequencies.
 * ******************************************************************************
 */

/**
 * ******************************************************************************
 * Example of proper sampling:
 *
 * f = 90 cycle/second sinusoid sampled at: fs = 1000 samples/second
 * This means: f = 0.09 * 1000
 *
 * So there are: 1000/90 = 11.1 samples taken over a complete cycle of a sinusoid
 * ******************************************************************************
 */

/**
 * ******************************************************************************
 * Value: 0x123
 *
 * Left adjusted: 0x1230
 * Right adjusted: 0x0123
 *
 * Advantage of left-justified: can take the most significant byte of the
 * register.
 *
 * ******************************************************************************
 */


