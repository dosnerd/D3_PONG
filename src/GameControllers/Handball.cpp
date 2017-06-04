/*
 * Handball.cpp
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#include <GameControllers/Handball.h>
#include <FPGA.h>
#include <gameEngine/Engine.h>
#include <gameEngine/GameObject.h>
#include <gameEngine/SideWall.h>
#include <gameEngine/FloorWall.h>
#include <gameEngine/Coordinate.h>
#include <GameControllers/PlayerController.h>
#include <config_file.h>

namespace GameControllers {

uint32_t Handball::sTopscore(0);

Handball::Handball(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2)
	: GameController(ball, player1, player2)
	, m_counter(0)
{
}

Handball::~Handball() {

}

void Handball::setupField(GameEngine::Engine* engine) {
	GameEngine::GameObject* wallFront = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
	GameEngine::GameObject* wallBack = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
	GameEngine::GameObject* wallLeft = new GameEngine::SideWall(100, 480);
	GameEngine::GameObject* wallRight = new GameEngine::SideWall(100, 480);
	GameEngine::GameObject* wallTop = new GameEngine::FloorWall(640, 100);
	GameEngine::GameObject* wallBottom = new GameEngine::FloorWall(640, 100);
	GameEngine::GameObject* playWall = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
	getBats()[GAMECONTROLLER_BAT1_PLAYER1] = new GameEngine::GameObject(GameEngine::Coordinate::Z, BAT_WITDH, BAT_HEIGHT);

	wallBack->setPosition(GameEngine::Coordinate(-320, -240, 80));
	wallFront->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallLeft->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallRight->setPosition(GameEngine::Coordinate(320, -240, 0));
	wallTop->setPosition(GameEngine::Coordinate(-320, 240, 0));
	wallBottom->setPosition(GameEngine::Coordinate(-320, -240, 0));
	playWall->setPosition(GameEngine::Coordinate(-320, -240, 72));
	getBats()[GAMECONTROLLER_BAT1_PLAYER1]->setPosition(GameEngine::Coordinate(-BAT_WITDH/2, -BAT_HEIGHT/2, 8));

	engine->addObject(wallFront);
	engine->addObject(wallBack);
	engine->addObject(wallLeft);
	engine->addObject(wallRight);
	engine->addObject(wallTop);
	engine->addObject(wallBottom);
	engine->addObject(playWall);
	engine->addObject(getBats()[GAMECONTROLLER_BAT1_PLAYER1]);

	getBall()->setPosition(GameEngine::Coordinate(0, 0, 40));
	getBall()->setSpeed(GameEngine::Coordinate(5, -3, 1));

	getPlayer(1)->setScore(1);
	getPlayer(2)->setScore(sTopscore);

	if (getFpga() != nullptr){
		getFpga()->setBall(engine->getBall());
		getFpga()->setBat(1, getBats()[GAMECONTROLLER_BAT1_PLAYER1]);
		getFpga()->setOption(FPGA_OPTION_HANDBAL_MODE | (getFpga()->getOptions() & FPGA_OPTION_MENU));
		getFpga()->update(FPGA_UPDATE_ALL);
	}
}

void Handball::updateScoreAndSpeed() {
	GameEngine::Coordinate ballSpeed = ballSpeed = getBall()->getSpeed();
	const GameEngine::Coordinate* ballPosition = &getBall()->getPosition();
	if (ballPosition->getZ() == 9) {
		getPlayer(1)->setScore(getPlayer(1)->getScore() + 1);

		if (getPlayer(2)->getScore() < getPlayer(1)->getScore())
			getPlayer(2)->setScore(getPlayer(1)->getScore());

		if (m_counter++ == 7) {
			m_counter = 0;
			if (ballSpeed.getZ() < 0) {
				getBall()->setSpeed(
						GameEngine::Coordinate(ballSpeed.getX(),
								ballSpeed.getY(), ballSpeed.getZ() - 1));
			} else {
				getBall()->setSpeed(
						GameEngine::Coordinate(ballSpeed.getX(),
								ballSpeed.getY(), ballSpeed.getZ() + 1));
			}
		}
	}
}

void Handball::onNotify() {
	GameController::onNotify();
	GameEngine::GameObject *bat = getBats()[GAMECONTROLLER_BAT1_PLAYER1];
	GameEngine::Coordinate positionPlayer = getPlayer(1)->getPosition();

	positionPlayer.setX(positionPlayer.getX() - bat->getWidth() / 2);
	positionPlayer.setY(positionPlayer.getY() - bat->getHeight() / 2);
	positionPlayer.setZ(bat->getPosition().getZ());

	bat->setPosition(positionPlayer);

	updateScoreAndSpeed();
	if (getFpga() != nullptr){
		getFpga()->update(FPGA_UPDATE_P1);
		getFpga()->printScore(getPlayer(1), 1, true);
		getFpga()->printScore(getPlayer(2), 2, true);
	}
}

void Handball::play(bool scoreAsNumber) {
	GameController::play(true);
	(void)scoreAsNumber;
}

void Handball::winMatch(uint8_t player) {
	uint32_t clock = 0xFFFFFF; //TODO: write good timer
	getPlayer(1)->setScore(0);
	m_counter = 0;

	while(clock--)
		asm("nop");
	(void)player;
}

} /* namespace GameControllers */
