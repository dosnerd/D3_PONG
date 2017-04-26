/*
 * FPGA.cpp
 *
 *  Created on: 25 apr. 2017
 *      Author: Acer
 */

#include <FPGA.h>
#include <stm32f4xx_conf.h>

FPGA FPGA::sInstance;

FPGA::FPGA() {
	GPIOinit();
}

FPGA::~FPGA() {

}

void FPGA::GPIOinit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure PA7 in output pushpull mode */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void FPGA::turnOn(){
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
}

void FPGA::turnOff(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
}

FPGA *FPGA::getInstance()
{
	return &sInstance;
}
