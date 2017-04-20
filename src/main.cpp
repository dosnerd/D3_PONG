#include <SPI.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

int main(void)
{
	volatile int i = 1;
	SPI comm;

	while(i){
		comm.write(7);
	}
}
