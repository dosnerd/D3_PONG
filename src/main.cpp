#include <LEDS.h>
#include <FPGA.h>
#include <Game.h>
#include <Buttons.h>

#include <UART.h>

#include <Menu/MenuBox.h>
#include <Menu/TextManager.h>

#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"
#include <string>

int main(void)
{
	volatile int16_t i = 0x55;
	bool pressed = false;
	LEDS *leds = LEDS::getInstance();
	Game *game = Game::getInstance();
	Menu::MenuItem *main = Menu::MenuBox::getInstance()->getCurrentMenu();

	for (i = 0; i < AMOUNTS_OF_LEDS; ++i) {
		leds->turnOff(i);
	}
	i = 1;

	FPGA::getInstance()->setOption(FPGA_OPTION_NONE);
	FPGA::getInstance()->setRegister(FPGA_REGISTER_STATE, 0x0);

	Menu::TextManager::clearAll();

	while(i){
		game->tick();
//		game->wait(0xFF);
		game->wait(0x85FFF);

		if (i & 0x4){
			leds->turnOn(LEDS::BLUE);
		}
		else{
			leds->turnOff(LEDS::BLUE);
		}

		i++;
		if (i & 0b1){
			if (Buttons::getInstace()->getButton()){
				if (!pressed){
					leds->turnOn(LEDS::GREEN);
					if (Menu::MenuBox::getInstance()->isShowing())
						Menu::MenuBox::getInstance()->select();
					else
						Menu::MenuBox::getInstance()->show(main);
					pressed = true;
				}
			} else {
				pressed = false;
				leds->turnOff(LEDS::GREEN);
			}
		}
		if (i == 30){
			i = 1;
			Menu::MenuBox::getInstance()->down();
		}
	}
}

