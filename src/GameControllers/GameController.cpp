/*
 * GameController.cpp
 *
 *  Created on: 11 mei 2017
 *      Author: Acer
 */

#include <GameControllers/GameController.h>
#include <gameEngine/Ball.h>
#include <gameEngine/SideWall.h>
#include <gameEngine/FloorWall.h>
#include <gameEngine/Engine.h>

#include <FPGA.h>

namespace GameControllers {

GameController::GameController(GameEngine::Ball *ball)
	: MVC::Controller(ball)
	, m_fpga(nullptr)
{
}

GameController::~GameController() {

}

void GameController::play() {
	getBall()->setSpeed(m_saveCoordinate);
}

void GameController::pause() {
	m_saveCoordinate = getBall()->getSpeed();
	getBall()->setSpeed(GameEngine::Coordinate(0, 0, 0));
}

void GameController::setupField(GameEngine::Engine* engine) {
	GameEngine::GameObject* wallFront = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
	GameEngine::GameObject* wallBack = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
	GameEngine::GameObject* wallLeft = new GameEngine::SideWall(100, 480);
	GameEngine::GameObject* wallRight = new GameEngine::SideWall(100, 480);
	GameEngine::GameObject* wallTop = new GameEngine::FloorWall(640, 100);
	GameEngine::GameObject* wallBottom = new GameEngine::FloorWall(640, 100);
	m_bat1 = new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);
	m_bat2= new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);

	wallBack->setPosition(GameEngine::Coordinate(-320, -240, 80));
	wallFront->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallLeft->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallRight->setPosition(GameEngine::Coordinate(320, -240, 0));
	wallTop->setPosition(GameEngine::Coordinate(-320, 240, 0));
	wallBottom->setPosition(GameEngine::Coordinate(-320, -240, 0));
	m_bat1->setPosition(GameEngine::Coordinate(-120, -90, 8));
	m_bat2->setPosition(GameEngine::Coordinate(-120, -90, 72));

	engine->addObject(wallFront);
	engine->addObject(wallBack);
	engine->addObject(wallLeft);
	engine->addObject(wallRight);
	engine->addObject(wallTop);
	engine->addObject(wallBottom);
	engine->addObject(m_bat1);
	engine->addObject(m_bat2);

	if (m_fpga != nullptr){
		m_fpga->setBall(engine->getBall());
		m_fpga->setBat(1, m_bat1);
		m_fpga->setBat(2, m_bat2);
		m_fpga->setOption(FPGA_OPTION_NONE);
	}
}

void GameController::winMatch() {
	uint32_t clock = 0xFFFFFF; //TODO: write good timer
	while(clock--)
		asm("nop");
}

void GameController::finishedGame() {
}

GameEngine::Ball* GameController::getBall() {
	return (GameEngine::Ball *)getModel();
}

void GameControllers::GameController::onNotify() {
	GameEngine::Coordinate *speed;
	const GameEngine::Coordinate *ballCoordinate = &getBall()->getPosition();

	resetNotifyFlag();
	if (ballCoordinate->getZ() > 72 || ballCoordinate->getZ() < 8){
		getBall()->setPosition(GameEngine::Coordinate(ballCoordinate->getX(), ballCoordinate->getY(), 40));
		speed = &getBall()->getSpeed();
		speed->flip(GameEngine::Coordinate::Z);

		winMatch();
	}

	m_fpga->update(FPGA_UPDATE_BALL);
}

void GameController::bind(FPGA* fpga) {
	m_fpga = fpga;
}

GameEngine::GameObject* GameController::getBat(uint8_t player) {
	switch(player){
	case 1:
		return m_bat1;

	case 2:
	default:
		return m_bat2;
	}
}

const FPGA* GameController::getFpga() const {
	return m_fpga;
}

} /* namespace GameControllers */
