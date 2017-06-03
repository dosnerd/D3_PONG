/*
 * FPGA.cpp
 *
 *  Created on: 25 apr. 2017
 *      Author: Acer
 */

#include <FPGA.h>
#include <stm32f4xx_conf.h>
#include <Stream.h>
#include <SPI.h>

#include <gameEngine/GameObject.h>
#include <gameEngine/Coordinate.h>

#include <Menu/TextManager.h>
#include <Menu/MenuBox.h>

#include <GameControllers/PlayerController.h>

#define ADDRESS_PLACE 	3*4
#define BALL			0
#define BAT_P1			1
#define BAT_P2			2

FPGA FPGA::sInstance(SPI::getInstance());
FPGA::FPGA(Stream *stream)
	: m_stream(stream)
{
	GPIOinit();
}

FPGA::~FPGA() {

}

void FPGA::update(uint8_t items) {
	GameEngine::Coordinate ballCoordinates = m_objects[BALL]->getPosition();
	GameEngine::Coordinate batP1Coordinates = m_objects[BAT_P1]->getPosition();
	GameEngine::Coordinate batP2Coordinates = m_objects[BAT_P2]->getPosition();

	if (items & FPGA_UPDATE_BALL){
		setRegister(FPGA_REGISTER_X_BALL, -ballCoordinates.getX() - (m_objects[BALL]->getWidth() / 2));
		setRegister(FPGA_REGISTER_Y_BALL, -ballCoordinates.getY() - (m_objects[BALL]->getHeight() / 2));
		setRegister(FPGA_REGISTER_Z_BALL, -ballCoordinates.getZ());
	}

	if (items & FPGA_UPDATE_P1){
		setRegister(FPGA_REGISTER_X_BAT_P1, -batP1Coordinates.getX() - (m_objects[BAT_P1]->getWidth() / 2));
		setRegister(FPGA_REGISTER_Y_BAT_P1, -batP1Coordinates.getY() - (m_objects[BAT_P1]->getHeight() / 2));

	}

	if (items & FPGA_UPDATE_P2){
		setRegister(FPGA_REGISTER_X_BAT_P2, -batP2Coordinates.getX() - (m_objects[BAT_P2]->getWidth() / 2));
		setRegister(FPGA_REGISTER_Y_BAT_P2, -batP2Coordinates.getY() - (m_objects[BAT_P2]->getHeight() / 2));
	}

	if (items & FPGA_UPDATE_OPTIONS){
		setRegister(FPGA_REGISTER_STATE, m_options);
	}
}

uint16_t FPGA::getOptions() const {
	return m_options;
}

void FPGA::GPIOinit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure PA7 in output pushpull mode */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * Turn on the FPGA power supply. WARNING: it take a few seconds
 * before the FPGA is ready
 */
void FPGA::turnOn(){
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
}

/**
 * Turn off the FPGA power supple.
 */
void FPGA::turnOff(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
}

/**
 * Get the instance
 */
FPGA *FPGA::getInstance()
{
	return &sInstance;
}

void FPGA::setBall(GameEngine::GameObject* ball) {
	m_objects[BALL] = ball;
}

void FPGA::setBat(uint8_t player, GameEngine::GameObject* bat) {
	if (player > 0 && player <= 2){
		m_objects[player] = bat;
	}
}

void FPGA::setOption(uint16_t options) {
	m_options = options;
	update(FPGA_UPDATE_OPTIONS);
}

void FPGA::setRegister(uint8_t reg, uint16_t value) {
	value &= 0x0FFF;
	value |= reg << ADDRESS_PLACE;

	m_stream->write(value);
}

void FPGA::printScore(GameControllers::PlayerController* player, uint8_t playerNumber, bool inNumbers) {
	uint16_t i;
	if (Menu::MenuBox::getInstance()->isShowing()){
		return;
	}

	Menu::TextManager::setColor(player->getColor());
	Menu::TextManager::setLine(1);
	if (playerNumber == 1)
		Menu::TextManager::setColumn(1);
	else
		Menu::TextManager::setColumn(69);

	Menu::TextManager::print("Player :");
	Menu::TextManager::printLine(Menu::TextManager::to_string(playerNumber));

	if (playerNumber == 1)
		Menu::TextManager::setColumn(1);
	else
		Menu::TextManager::setColumn(69);

	if (inNumbers)
		Menu::TextManager::print(Menu::TextManager::to_string(player->getScore()) + "       ");
	else {
		for (i = 0; i < player->getScore(); ++i) {
			Menu::TextManager::print(std::string({(char)0x03}));
		}
		Menu::TextManager::print(" ");
	}
}
