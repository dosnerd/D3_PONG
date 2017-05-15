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
	GameEngine::GameObject* bat1 = new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);
	GameEngine::GameObject* bat2= new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);

	wallBack->setPosition(GameEngine::Coordinate(-320, -240, 80));
	wallFront->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallLeft->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallRight->setPosition(GameEngine::Coordinate(320, -240, 0));
	wallTop->setPosition(GameEngine::Coordinate(-320, 240, 0));
	wallBottom->setPosition(GameEngine::Coordinate(-320, -240, 0));
	bat1->setPosition(GameEngine::Coordinate(-120, -90, 8));
	bat2->setPosition(GameEngine::Coordinate(-120, -90, 72));

	engine->addObject(wallFront);
	engine->addObject(wallBack);
	engine->addObject(wallLeft);
	engine->addObject(wallRight);
	engine->addObject(wallTop);
	engine->addObject(wallBottom);
	engine->addObject(bat1);
	engine->addObject(bat2);

	if (m_fpga != nullptr){
		m_fpga->setBall(engine->getBall());
		m_fpga->setBat(1, bat1);
		m_fpga->setBat(2, bat2);
		m_fpga->setOption(FPGA_OPTION_NONE);
	}
}

void GameController::winMatch() {
}

void GameController::finishedGame() {
}

GameEngine::Ball* GameController::getBall() {
	return (GameEngine::Ball *)getModel();
}

void GameControllers::GameController::onNotify() {
	resetNotifyFlag();

	m_fpga->update(FPGA_UPDATE_BALL);
}

void GameController::bind(FPGA* fpga) {
	m_fpga = fpga;
}

const FPGA* GameController::getFpga() const {
	return m_fpga;
}

} /* namespace GameControllers */
