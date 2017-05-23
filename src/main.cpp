#include <SPI.h>
#include <UART.h>
#include <LEDS.h>
#include <FPGA.h>
#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

void delay(uint32_t time);
uint16_t UARTCHECK(LEDS *leds, UART *uartInstance, uint16_t i);


int main(void)
{
	volatile uint8_t i = 0x55;
	uint8_t addres = 0x01;
	SPI	*spiInstance = SPI::getInstance();
	UART *uartInstance = UART::getInstance();
	LEDS *leds = LEDS::getInstance();
	FPGA *fpga = FPGA::getInstance();

	for (i = 0; i < AMOUNTS_OF_LEDS; ++i) {
		leds->turnOff(i);
	}
	i = 1;

	while(i){

		delay(0xFFFFF);
		//delay(0x200000);

		spiInstance->write((addres << (3*4)) | i);
		uartInstance->write(UARTCHECK(leds, uartInstance, 0x55));

		if (i & 0x4){
			leds->turnOn(LEDS::BLUE);
			fpga->turnOn();
		}
		else{
			leds->turnOff(LEDS::BLUE);
			fpga->turnOff();
		}

		i++;
		if (i == 0){
			i = 1;
			addres++;

			if (addres > 0b0111){
				addres = 1;
			}
		}
	}
}

uint16_t UARTCHECK(LEDS *leds, UART *uartInstance, uint16_t i){
	uint16_t buffer = 0;

	while (uartInstance->getBufferLenght()) {
		buffer = uartInstance->read();
		if (buffer == i) {
			leds->turnOn(LEDS::GREEN);
			leds->turnOff(LEDS::RED);
		} else {
			leds->turnOn(LEDS::RED);
			leds->turnOff(LEDS::GREEN);
		}
	}

	return buffer;
}

void delay(uint32_t time){
	//block for time
	while(time--) {
		asm volatile ("nop");
	}
}
