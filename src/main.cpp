#include <SPI.h>
#include <UART.h>
#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

void delay(uint32_t time);

int main(void)
{
	volatile uint8_t i = 0x55;
	uint16_t buffer;
#if SPI_INTERRUPT_ENABLE
	SPI spiInstance = SPI::sInstance;
#else
	SPI spiInstance;
#endif
#if UART_INTERRUPT_ENABLE
	UART uartInstance = UART::sInstance;
#else
	UART uartInstance;
#endif

	while(i){
		spiInstance.write(i);
		uartInstance.write(i);
		delay(0x3FFFFF);

		buffer = uartInstance.read();
		if (buffer == i) {
			//green
		} else if (buffer > i) {
			//other than previous
		} else if (buffer < i){
			//other then previous
		}
	}
}

void delay(uint32_t time){
	//block for time
	while(time--) {
		asm volatile ("nop");
	}
}
