#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

void delay(uint32_t time);

int main(void)
{
}

void delay(uint32_t time){
	//block for time
	while(time--) {
		asm volatile ("nop");
	}
}
