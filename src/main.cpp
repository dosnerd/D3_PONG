#include <LEDS.h>
#include <FPGA.h>
#include <Game.h>
#include <Buttons.h>

#include <UART.h>
#include <TimingControl.h>

#include <Menu/MenuBox.h>
#include <Menu/TextManager.h>

#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"
#include <string>

int main(void)
{
	volatile int8_t i = 0x55;
	bool pressed = false, blueOn=false;
	LEDS *leds = LEDS::getInstance();
	Game *game = Game::getInstance();
	TimingControl *timer = TimingControl::getInstance();

	for (i = 0; i < AMOUNTS_OF_LEDS; ++i) {
		leds->turnOff(i);
	}
	i = 1;

	FPGA::getInstance()->setOption(FPGA_OPTION_NONE);
	FPGA::getInstance()->setRegister(FPGA_REGISTER_STATE, 0x0);

	Menu::TextManager::clearAll();

	game->openMainMenu();

	while(i){
		if (timer->isDone(GAME_TIMER)){
			timer->setDelay(GAME_TIMER, 0x2D0000);
			game->tick();

		}
		if (timer->isDone(ANIMATION_TIMER)){
			timer->setDelay(ANIMATION_TIMER, 0x2B0000);
			game->animateMenu();
			leds->turnOff(LEDS::ORANGE);
		}
		if (timer->isDone(SYNC_TIMER)){
			timer->setDelay(SYNC_TIMER, 0xFFFFFFF);
			FPGA::getInstance()->update(FPGA_UPDATE_ALL);
			leds->turnOn(LEDS::ORANGE);
		}
		if (timer->isDone(MENU_TEST_TIMER)){
			timer->setDelay(MENU_TEST_TIMER, 0x4000000);
			Menu::MenuBox::getInstance()->down();

			if (blueOn){
				leds->turnOff(LEDS::BLUE);
				blueOn = false;
			}
			else{
				leds->turnOn(LEDS::BLUE);
				blueOn = true;
			}
		}
		MVC::Observer::handleNotifications();

		if (++i > 0x55) i = 1;
		if (i & 0b10000){
			if (Buttons::getInstace()->getButton()){
				if (!pressed){
					if (Menu::MenuBox::getInstance()->isShowing())
						Menu::MenuBox::getInstance()->select();
					else
						game->pause();
					pressed = true;
				}
			} else
				pressed = false;
		}
	}
}

