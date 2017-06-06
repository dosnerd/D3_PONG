/*
 * Buttons.cpp
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#include <Buttons.h>
#include <stm32f4xx_conf.h>

Buttons Buttons::sInstance;
Buttons::Buttons() {

	  GPIO_InitTypeDef GPIO_InitStructure;

	  /* Enable the BUTTON Clock */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	  /* Configure Button pin as input */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

Buttons::~Buttons() {

}

bool Buttons::getButton() {
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_SET;
}

Buttons* Buttons::getInstace() {
	return &sInstance;
}
