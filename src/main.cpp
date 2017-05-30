#include <LEDS.h>
#include <FPGA.h>

#include <gameEngine/Engine.h>
#include <GameControllers/Tennis.h>
#include <GameControllers/Demo.h>

#include <Menu/TextManager.h>
#include <Menu/MenuController.h>
#include <Menu/MainMenu.h>

#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"
#include <string>

void delay(uint32_t time);

int main(void)
{
	Menu::TextManager::clearAll();
	Menu::TextManager::print("Loading...");

	volatile int16_t i = 0x55;
	Menu::MainMenu mainMenu;
	LEDS *leds = LEDS::getInstance();
	FPGA *fpga = FPGA::getInstance();
	GameEngine::Engine *engine = new GameEngine::Engine();
	GameControllers::Demo controller(engine->getBall());

	controller.bind(fpga);
	controller.setupField(engine);

	fpga->turnOn();
	for (i = 0; i < AMOUNTS_OF_LEDS; ++i) {
		leds->turnOff(i);
	}
	i = 1;

	Menu::MenuController::getInstance()->show(&mainMenu);

	while(i){
		engine->moveBall();
		MVC::Observer::handleNotifications();
		fpga->update(FPGA_UPDATE_ALL);

		Menu::TextManager::setColumn(0);
		Menu::TextManager::setLine(0);
		Menu::TextManager::printLine("Playing   ");

		delay(0x85FFF);
		if (i & 0x4){
			leds->turnOn(LEDS::BLUE);
		}
		else{
			leds->turnOff(LEDS::BLUE);
		}

		i++;
		if (i >= 150){
			i = 1;
			mainMenu.down();
			Menu::MenuController::getInstance()->print();
		}
	}
}

void delay(uint32_t time){
	//block for time
	while(time--) {
		asm volatile ("nop");
	}
}
