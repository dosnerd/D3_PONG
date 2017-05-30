#include <SPI.h>
#include <UART.h>
#include <LEDS.h>
#include <FPGA.h>
#include <MDAC.h>
#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"
#include <Math.h>

void delay(uint32_t time);

#define PI 				3.141592

int main(void) {

	// double ySine = 0.0;

	/*__asm("  LDR.W R0, =0xE000ED88\n"
	        "  LDR R1, [R0]\n"
	        "  ORR R1, R1, #(0xF << 20)\n"
	        "  STR R1, [R0]");*/


	MDAC *dac = MDAC::getInstance();
	LEDS *led = LEDS::getInstance();
//	 volatile uint16_t i;
	// volatile uint16_t j;

	double y[3] = { 0, 0, 0 };
//
	double point;
	double frequency = 1000;
	double samplingFrequency = 8000;

	y[1] = sin( -1 * 2 * PI * frequency / samplingFrequency );
	y[2] = sin( -2 * 2 * PI * frequency / samplingFrequency );
	point = 2 * cos( 2 * PI * frequency / samplingFrequency );

	do {
		y[0] = point * y[1] - y[2];
		y[2] = y[1];
		y[1] = y[0];

		dac->setData(1000*y[0]);
		delay(0xFF);
	} while (true);
	 // y[1] = sin( -1 * 2 * PI * frequency / samplingFrequency );
	 // y[2] = sin( -2 * 2 * PI * frequency / samplingFrequency );
	//  point = 2 * cos( 2 * PI * frequency / samplingFrequency );

	 //double time = 0.0;

	 // double i;
	 // int j;

	 // double sineWave;

	 bool on = false;
	while (true) {
		on=!on;
		if (on)
			led->turnOff(LEDS::BLUE);
		else
			led->turnOn(LEDS::BLUE);

		// i = 0.0;

		/*do {
			ySine = (sin(i * (2*PI)/4000) + 1) * ((0xFFF + 1) / 2);
			// dac->setData(ySine);
			i+=1.0;
		} while (i < 8000.0);*/


		// delay(0xFFFFFF);
		// led->turnOff(LEDS::BLUE);
		// delay(0xFFFFFF);
		//time =+ 1.25E-04;

		// y = amplitude × sin(frequency×time+phase)+bias.
		// sineWave = 2048 * sin( frequency * 2 * PI * time ) + 2048;

		// time =+ 1.25E-04;

		/*if (time >= 1.0) {
			time = 0.0;
		}*/

		// double sineWave = sin( -1 * 2 * PI * frequency / samplingFrequency );

		// y[0] = point * y[1] - y[2];
		// y[2] = y[1];
		// y[1] = y[0];
		// uint32_t roundTest = 0;

		/*for (i = 0; i < 4096.0; ++i) {
//					double theta = i / 8000 * 1.0 * 2.0 * PI;
					float theta = 4096 * sin(i);
					(void)theta;*/


		// asm("VCVT.U32.F32 roundTest, theta");
		// dac->setData(roundTest);





		/*do {
			double sineWave = 2048.0*sin(2.0*PI*(1.0/i));



			dac->setData(sineWave);
			delay(0xFF);
			i++;
		} while (i < 4000);*/
		// }
		// }



		// dac->setData(sineWave);		//
		// delay(0xFFFFF);

//		for (j = 0xD; j < 0x30; ++j) {
//			for (i = 0; i < 0xFFFF; ++i) {
//				dac->setData(i);
//
//				delay(j);
//			}
//		}



	}
}

/*
void generateSinusoid() {

}*/

void delay(uint32_t time) {
	//block for time
	while (time--) {
		asm volatile ("nop");
	}
}

