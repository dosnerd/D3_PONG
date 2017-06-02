/*
 * PlayerController.cpp
 *
 *  Created on: 30 mei 2017
 *      Author: Acer
 */

#include <GameControllers/PlayerController.h>
#include <Stream.h>

#include <Menu/TextManager.h>

#define COMMAND_NONE		0x00
#define COMMAND_POSITION 	0x01
#define COMMAND_ACTION 		0x02
#define COMMAND_BATTERY 	0x03

namespace GameControllers {

PlayerController::PlayerController(Stream *stream)
	: MVC::Controller(stream)
	, m_score(0)
	, m_color(0xFFF)
	, m_cmd(COMMAND_NONE)
	, m_stream(stream)
	, m_position(0,0,0)
{
}

PlayerController::~PlayerController() {

}

uint16_t PlayerController::getScore() const {
	return m_score;
}

uint16_t PlayerController::getColor() const {
	return m_color;
}

void PlayerController::setScore(uint16_t score) {
	m_score = score;
}

void PlayerController::setColor(uint16_t color) {
	m_color = color;
}

void PlayerController::readPosition() {
	if (m_stream->getBufferLenght() >= 2) {
		m_position.setX((int8_t)m_stream->read());
		m_position.setY((int8_t)m_stream->read());
		m_cmd = COMMAND_NONE;
	}
}

void PlayerController::runCommand() {
	switch (m_cmd) {
	case COMMAND_POSITION:
		readPosition();
		return;
	case COMMAND_NONE:
	default:
		m_cmd = COMMAND_NONE;
		return;
	}
}

void PlayerController::onNotify() {
	resetNotifyFlag();

	//resume old command
	if (m_cmd != COMMAND_NONE)
		runCommand();

	//run new commands
	while(m_cmd == COMMAND_NONE && m_stream->getBufferLenght() > 0){
		m_cmd = (int8_t)m_stream->read();
		runCommand();
	}
}

GameEngine::Coordinate PlayerController::getPosition() const {
	return m_position;
}

} /* namespace GameControllers */
