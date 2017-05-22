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

#include <DAC.h>
#include <Vector.h>
#include <stm32f4xx_conf.h>

// NOTE: Methods have been defined in the source files already. Why create your own?

DAC DAC::sInstance;

DAC::DAC() {

}

// TODO: finish initialization method
void DAC::DACinit() {
	DAC_OutputBuffer DAC_InitStructure;
	DAC_InitStruc
}

// TODO: create method: select trigger

// TODO: create method: select wave generation

// TODO: create method: select triangle amplitude

// TODO: create method: select DAC output buffer

// TODO: create method: select DAC channel

// TODO: create method: align DAC data

// TODO: create method:

// TODO: create method:
