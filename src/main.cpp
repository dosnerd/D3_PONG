#include <SPI.h>
#include <UART.h>
#include <LEDS.h>
#include <FPGA.h>

#include <gameEngine/Engine.h>
#include <gameEngine/SideWall.h>
#include <gameEngine/FloorWall.h>

#include <config_file.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

void delay(uint32_t time);
void SPI_write(uint16_t address, uint16_t value);
uint16_t UARTCHECK(LEDS *leds, UART *uartInstance, uint16_t i);

GameEngine::Engine *getEngine();

int main(void)
{
	volatile int16_t i = 0x55;
	uint8_t addres = 0x01;
	SPI	*spiInstance = SPI::getInstance();
	UART *uartInstance = UART::getInstance(4);
	LEDS *leds = LEDS::getInstance();
	FPGA *fpga = FPGA::getInstance();
	GameEngine::Engine *engine = getEngine();
	GameEngine::Ball *ball = engine->getBall();

	GameEngine::GameObject* bat1 = new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);
	GameEngine::GameObject* bat2= new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);
	bat1->setPosition(GameEngine::Coordinate(-120, -90, 8));
	bat2->setPosition(GameEngine::Coordinate(-120, -90, 72));

	engine->addObject(bat1);
	engine->addObject(bat2);

	engine->getBall()->setPosition(GameEngine::Coordinate(-30, -30, 9));
	engine->getBall()->setSpeed(GameEngine::Coordinate(7, -3, 	1));

	for (i = 0; i < AMOUNTS_OF_LEDS; ++i) {
		leds->turnOff(i);
	}
	i = 100;



	while(i){

		engine->moveBall();

		SPI_write(0x1, -ball->getPosition().getX() - (ball->getWidth() / 2));
		SPI_write(0x2, -ball->getPosition().getY() - (ball->getWidth() / 2));
		SPI_write(0x3, -ball->getPosition().getZ());

		uartInstance->write(UARTCHECK(leds, uartInstance, 0x55));

		SPI_write(0x4, -bat1->getPosition().getX() - (bat1->getWidth() / 2));
		SPI_write(0x5, -bat1->getPosition().getY() - (bat1->getHeight() / 2));

		SPI_write(0x6, -bat2->getPosition().getX() - (bat2->getWidth() / 2));
		SPI_write(0x7, -bat2->getPosition().getY() - (bat2->getHeight() / 2));
		SPI_write(0xF, 0);

		delay(0x85FFF);
		if (i & 0x4){
			leds->turnOn(LEDS::BLUE);
			fpga->turnOn();
		}
		else{
			leds->turnOff(LEDS::BLUE);
			fpga->turnOff();
		}

		i--;
		if (i <= 8){
			i = 100;
			addres++;

			if (addres > 0b0111){
				addres = 1;
			}
		}
	}
}

GameEngine::Engine *getEngine(){
	GameEngine::Engine* engine = new GameEngine::Engine();
		GameEngine::GameObject* wallFront = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
		GameEngine::GameObject* wallBack = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
		GameEngine::GameObject* wallLeft = new GameEngine::SideWall(100, 480);
		GameEngine::GameObject* wallRight = new GameEngine::SideWall(100, 480);
		GameEngine::GameObject* wallTop = new GameEngine::FloorWall(640, 100);
		GameEngine::GameObject* wallBottom = new GameEngine::FloorWall(640, 100);
//		GameEngine::GameObject* bat1 = new GameEngine::GameObject(GameEngine::Coordinate::Z, 120, 80);
//		GameEngine::GameObject* bat2 = new GameEngine::GameObject(GameEngine::Coordinate::Z, 120, 80);


		wallBack->setPosition(GameEngine::Coordinate(-320, -240, 80));
		wallFront->setPosition(GameEngine::Coordinate(-320, -240, 0));
		wallLeft->setPosition(GameEngine::Coordinate(-320, -240, 0));
		wallRight->setPosition(GameEngine::Coordinate(320, -240, 0));
		wallTop->setPosition(GameEngine::Coordinate(-320, 240, 0));
		wallBottom->setPosition(GameEngine::Coordinate(-320, -240, 0));
//		bat1->setPosition(GameEngine::Coordinate(200, 50, 8));
//		bat2->setPosition(GameEngine::Coordinate(-100, -50, 72));

		engine->addObject(wallFront);
		engine->addObject(wallBack);
		engine->addObject(wallLeft);
		engine->addObject(wallRight);
		engine->addObject(wallTop);
		engine->addObject(wallBottom);
//		engine->addObject(bat1);
//		engine->addObject(bat2);

	return engine;
}

void SPI_write(uint16_t address, uint16_t value){
	uint16_t buff = address << 3*4;
	buff |= value & 0xFFF;
	SPI::getInstance()->write(buff);
}

uint16_t UARTCHECK(LEDS *leds, UART *uartInstance, uint16_t i){
	uint16_t buffer = 0;

	while (uartInstance->getBufferLenght()) {
		buffer = uartInstance->read();
		if (buffer == i) {
			leds->turnOn(LEDS::GREEN);
			leds->turnOff(LEDS::RED);
		} else {
			leds->turnOn(LEDS::RED);
			leds->turnOff(LEDS::GREEN);
		}
	}

	return buffer;
}

void delay(uint32_t time){
	//block for time
	while(time--) {
		asm volatile ("nop");
	}
}
