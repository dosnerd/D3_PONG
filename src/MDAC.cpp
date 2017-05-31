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
  *
  * The DAC module is a 12-bit, voltage output digital-to-analog converter. It may
 * be used in conjunction with the DMA controller. For this project, a noise wave
 * is generated.
 *
 * Digital to analog conversions allow computers to interact with analog signals.
  ******************************************************************************
  */

#include "../inc/MDAC.h"
#include <Vector.h>
#include <stm32f4xx_conf.h>

MDAC MDAC::sInstance;

/*******************************************************************************/

/**
  * @brief  Configures DAC channel 1.
  * @retval None
  */
MDAC::MDAC(void) {
	GPIOinit();
	DACinit(DAC_Channel_1);
}

/*******************************************************************************/

/**
  * @brief  Configures analog pins on pin 4.
  * @retval None
  */
void MDAC::GPIOinit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  Configures clock, max amplitude, buffer, and noise-wave generation
  *  		of the corresponding DAC channel. This configuration does not use an interrupt.
  * @param  channel: The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_Channel_1: DAC Channel1 selected
  *            @arg DAC_Channel_2: DAC Channel2 selected
  * @retval None
  */
void MDAC::DACinit(uint32_t channel) {
	DAC_InitTypeDef DAC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Noise;
	DAC_Init(channel, &DAC_InitStructure);
	DAC_Cmd(channel, ENABLE);
	DAC_DualSoftwareTriggerCmd(DISABLE);
	DAC_WaveGenerationCmd(channel, DAC_Wave_Noise, ENABLE);
}

/**
  * @brief  Set data to be transmitted. No interrupt needed
  * 		Automatically transmits data when set.
  * @param  data: The data to be transmitted to output buffer.
  * @retval None
  */
void MDAC::setData(uint16_t data) {
	DAC_SetChannel1Data(DAC_Align_12b_R, data);
}

void MDAC::setFrequency(uint16_t frequency) {

}

uint16_t getChannel1Data(void) {
	return DAC_GetDataOutputValue(DAC_Channel_1);
}

/**
  * @brief  Get the instance of the current object.
  * @retval *MDAC
  */
MDAC *MDAC::getInstance() {
	return &sInstance;
}

MDAC::~MDAC() {}

/*******************************************************************************/
