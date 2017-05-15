#include <LEDS.h>
#include <FPGA.h>

#include <gameEngine/Engine.h>
#include <GameControllers/GameController.h>


#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

void delay(uint32_t time);

int main(void)
{
	volatile int16_t i = 0x55;
	LEDS *leds = LEDS::getInstance();
	FPGA *fpga = FPGA::getInstance();
	GameEngine::Engine *engine = new GameEngine::Engine();
	GameControllers::GameController controller(engine->getBall());

	controller.bind(fpga);
	controller.setupField(engine);

	engine->getBall()->setPosition(GameEngine::Coordinate(-30, -30, 9));
	engine->getBall()->setSpeed(GameEngine::Coordinate(7, -3, 	1));

	fpga->turnOn();
	for (i = 0; i < AMOUNTS_OF_LEDS; ++i) {
		leds->turnOff(i);
	}
	i = 100;



	while(i){
		engine->moveBall();
		MVC::Observer::handleNotifications();

		delay(0x85FFF);
		if (i & 0x4){
			leds->turnOn(LEDS::BLUE);
		}
		else{
			leds->turnOff(LEDS::BLUE);
		}

		i--;
		if (i <= 8){
			i = 100;
		}
	}
}

void delay(uint32_t time){
	//block for time
	while(time--) {
		asm volatile ("nop");
	}
}
