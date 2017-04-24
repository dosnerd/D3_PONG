/*
 * LEDS.cpp
 *
 *  Created on: 24 apr. 2017
 *      Author: Acer
 */

#include <LEDS.h>

LEDS::LEDS(bool init) {
	if (init)
		GPIOinit();
}

LEDS::~LEDS() {

}

void LEDS::GPIOinit() {
	GPIO_InitTypeDef GPIO_InitStructure;
	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void LEDS::turnOn(const uint8_t led){
	if (led >= 0 && led < AMOUNTS_OF_LEDS) {
		GPIO_SetBits(GPIOD, leds[led]);
	}
}

void LEDS::turnOff(const uint8_t led){
	if (led >= 0 && led < AMOUNTS_OF_LEDS) {
		GPIO_ResetBits(GPIOD, leds[led]);
	}
}
