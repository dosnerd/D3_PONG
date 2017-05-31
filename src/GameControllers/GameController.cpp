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
#include <GameControllers/PlayerController.h>

#include <FPGA.h>

namespace GameControllers {

GameController::GameController(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2)
	: MVC::Controller(ball)
	, m_fpga(nullptr)
	, m_bats{nullptr, nullptr, nullptr, nullptr}
	, m_player1(player1)
	, m_player2(player2)
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
	m_bats[GAMECONTROLLER_BAT1_PLAYER1] = new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);
	m_bats[GAMECONTROLLER_BAT1_PLAYER2] = new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);

	wallBack->setPosition(GameEngine::Coordinate(-320, -240, 80));
	wallFront->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallLeft->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallRight->setPosition(GameEngine::Coordinate(320, -240, 0));
	wallTop->setPosition(GameEngine::Coordinate(-320, 240, 0));
	wallBottom->setPosition(GameEngine::Coordinate(-320, -240, 0));
	m_bats[GAMECONTROLLER_BAT1_PLAYER1]->setPosition(GameEngine::Coordinate(-120, -90, 8));
	m_bats[GAMECONTROLLER_BAT1_PLAYER2]->setPosition(GameEngine::Coordinate(-120, -90, 72));

	engine->addObject(wallFront);
	engine->addObject(wallBack);
	engine->addObject(wallLeft);
	engine->addObject(wallRight);
	engine->addObject(wallTop);
	engine->addObject(wallBottom);
	engine->addObject(m_bats[GAMECONTROLLER_BAT1_PLAYER1]);
	engine->addObject(m_bats[GAMECONTROLLER_BAT1_PLAYER2]);

	getBall()->setPosition(GameEngine::Coordinate(0, 0, 40));

	m_player1->setScore(5);
	m_player2->setScore(5);

	if (m_fpga != nullptr){
		m_fpga->setBall(engine->getBall());
		m_fpga->setBat(1, m_bats[GAMECONTROLLER_BAT1_PLAYER1]);
		m_fpga->setBat(2, m_bats[GAMECONTROLLER_BAT1_PLAYER2]);
		m_fpga->setOption(FPGA_OPTION_NONE);
	}
}

void GameController::winMatch(uint8_t player) {
	uint32_t clock = 0xFFFFFF; //TODO: write good timer
	if (player == 2){
		m_player1->setScore(m_player1->getScore() - 1);
		if (m_player1->getScore() == 0){
			finishedGame();
		}
	}
	else{
		m_player2->setScore(m_player2->getScore() - 1);
		if (m_player2->getScore() == 0){
			finishedGame();
		}
	}

	if (m_fpga != nullptr){
		m_fpga->printScore(m_player1, 1);
		m_fpga->printScore(m_player2, 2);
	}

	while(clock--)
		asm("nop");
}

void GameController::finishedGame() {
	m_player1->setScore(5);
	m_player2->setScore(5);
}

GameEngine::Ball* GameController::getBall() {
	return (GameEngine::Ball *)getModel();
}

void GameControllers::GameController::onNotify() {
	const GameEngine::Coordinate *ballCoordinate = &getBall()->getPosition();

	resetNotifyFlag();
	if (ballCoordinate->getZ() > 72 || ballCoordinate->getZ() < 8){
		winMatch((ballCoordinate->getZ() > 72) + 1);

		//TODO: Randomize speed? + position
		getBall()->setPosition(GameEngine::Coordinate(ballCoordinate->getX(), ballCoordinate->getY(), 40));
		if (getBall()->getSpeed().getZ() < 0)
			getBall()->setSpeed(GameEngine::Coordinate(5, -3, 1));
		else
			getBall()->setSpeed(GameEngine::Coordinate(5, -3, -1));
	}

	if (m_fpga != nullptr)
		m_fpga->update(FPGA_UPDATE_BALL);
}

void GameController::bind(FPGA* fpga) {
	m_fpga = fpga;
}

GameEngine::GameObject** GameController::getBats() {
	return m_bats;
}

const FPGA* GameController::getFpga() const {
	return m_fpga;
}

} /* namespace GameControllers */
