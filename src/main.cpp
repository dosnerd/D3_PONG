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
	MDAC *dac = MDAC::getInstance();


	double y[3] = { 0, 0, 0 };
	//
	double point;
	double frequency = 1.0;
	double samplingFrequency = 4096.0;

	y[1] = sin( -1 * 2 * PI * frequency / samplingFrequency );
	y[2] = sin( -2 * 2 * PI * frequency / samplingFrequency );
	point = 2 * cos( 2 * PI * frequency / samplingFrequency );

	do {

		y[0] = point * y[1] - y[2];
		y[2] = y[1];
		y[1] = y[0];

		dac->setData(2048*(y[0]) + 2048);

	} while (true);









	// LEDS *led = LEDS::getInstance();

	// uint16_t volatile i;
	// double i;
	//uint16_t volatile j;
	// float sampleRate = 8000.0;

	// float m_amplitude = 0.5, m_frequency = 500, m_phase = 0.0, m_time = 0.0, m_deltaTime = 1 / sampleRate;
	// (uint16_t) 2048*sin(i*2*PI*0.001)
	// double amplitude = (0xFFF + 1) / 2;

	// double sineWave = (sin(1 * (2*PI/800)) + 1) * amplitude;


	// while (1) {

		// for (i = 0 ; i < 4096; i++) {
			// dac->setData(i);
		// }
		// for (i = 4096 ; i > 0; i--) {
			// dac->setData(sineWave);
		// }
	// }
}

void delay(uint32_t time) {
	//block for time
	while (time--) {
		asm volatile ("nop");
	}
}

