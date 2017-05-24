#include <SPI.h>
#include <UART.h>
#include <LEDS.h>
#include <FPGA.h>
#include <MDAC.h>
#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

void delay(uint32_t time);

int main(void) {
	MDAC *dac = MDAC::getInstance();
	volatile uint16_t i;
	volatile uint16_t j;

	while (true) {
		for (j = 0xD; j < 0x30; ++j) {
			for (i = 0; i < 0xFFFF; ++i) {
				dac->setData(i);

				delay(j);
			}
		}
	}
}

void delay(uint32_t time) {
	//block for time
	while (time--) {
		asm volatile ("nop");
	}
}
