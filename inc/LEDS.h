/*
 * LEDS.h
 *
 *  Created on: 24 apr. 2017
 *      Author: Acer
 */

#ifndef INC_LEDS_H_
#define INC_LEDS_H_

#include <stm32f4xx_conf.h>
#define AMOUNTS_OF_LEDS 4

#ifdef __cplusplus

class LEDS {
public:
	virtual 				~LEDS();

private:
							LEDS();

public:
	virtual void			turnOn(const uint8_t led);
	virtual void			turnOff(const uint8_t led);
	virtual void			infiniteBlink(const uint8_t led, uint32_t speed);

public:
	static LEDS				*getInstance();

public:
	enum LED {
		GREEN,
		ORANGE,
		RED,
		BLUE
	};

private:
	uint32_t 				leds[AMOUNTS_OF_LEDS] = {
											GPIO_Pin_12,
											GPIO_Pin_13,
											GPIO_Pin_14,
											GPIO_Pin_15
							};
	static LEDS				sInstance;

	void GPIOinit();
};
extern "C" {
#endif

void blinkLight(uint8_t led, uint32_t speed);

#ifdef __cplusplus
}
#endif
#endif /* INC_LEDS_H_ */
