/*
 * LEDS.cpp
 *
 *  Created on: 24 apr. 2017
 *      Author: Acer
 */

#include <LEDS.h>

LEDS LEDS::sInstance;

LEDS::LEDS() {
	GPIOinit();
}

LEDS::~LEDS() {

}

void LEDS::GPIOinit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
 * Turn on a specific LED. The given parameter is
 * the index of the led saved in a led array. For
 * the correct color, please use the LED enum.
 */
void LEDS::turnOn(const uint8_t led){
	if (led < AMOUNTS_OF_LEDS) {
		GPIO_SetBits(GPIOD, leds[led]);
	}
}

/**
 * Turn off a specific LED. The given parameter is
 * the index of the led saved in a led array. For
 * the correct color, please use the LED enum.
 */
void LEDS::turnOff(const uint8_t led){
	if (led < AMOUNTS_OF_LEDS) {
		GPIO_ResetBits(GPIOD, leds[led]);
	}
}

void LEDS::infiniteBlink(const uint8_t led, uint32_t speed) {
	uint32_t time;

	if (led < AMOUNTS_OF_LEDS) {
		while (true) {
			time = speed;
			while(time--) {
				asm("nop");
			}
			GPIO_ToggleBits(GPIOD, leds[led]);
		}
	}
}

/**
 * Get the instance
 */
LEDS *LEDS::getInstance(){
	return &sInstance;
}

void blinkLight(uint8_t led, uint32_t speed) {
	LEDS::getInstance()->infiniteBlink(led, speed);
}
