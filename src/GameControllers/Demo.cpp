/*
 * Demo.cpp
 *
 *  Created on: 16 mei 2017
 *      Author: Acer
 */

#include <GameControllers/Demo.h>
#include <gameEngine/Ball.h>
#include <gameEngine/GameObject.h>
#include <stdlib.h>

#define MAX_BAT_SPEED 12

namespace GameControllers {

Demo::Demo(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2)
	: GameController(ball, player1, player2)
	, m_counter(0)
{
}

Demo::~Demo() {
}

const GameEngine::Coordinate* Demo::getBallPosition(
		const GameEngine::Coordinate& ballSpeed,
		uint8_t player)
{
	const GameEngine::Coordinate* ballCoordinate;
	GameEngine::Coordinate center(
			-getBats()[1]->getWidth() / 2,
			-getBats()[1]->getHeight() / 2, 0);

	if (ballSpeed.getZ() > 0 && player == 1) {
		ballCoordinate = &center;
	} else if (ballSpeed.getZ() < 0 && player == 2) {
		ballCoordinate = &center;
	} else {
		ballCoordinate = &getBall()->getPosition();
	}

	return ballCoordinate;
}

GameEngine::Coordinate Demo::calcBatNewPosition(
		const GameEngine::Coordinate* batPosition,
		const GameEngine::Coordinate& batSpeed)
{
	GameEngine::Coordinate batNewPosition = (*batPosition) - batSpeed;
	if (abs(batNewPosition.getX()) > 420) {
		batNewPosition.setX(batNewPosition.getX() < 0 ? -420 : 420);
	}
	if (abs(batNewPosition.getY()) > 240) {
		batNewPosition.setY(batNewPosition.getY() < 0 ? -240 : 240);
	}
	return batNewPosition;
}

GameEngine::Coordinate Demo::calcBatSpeed(uint8_t player, const GameEngine::Coordinate* batPosition) {
	GameEngine::Coordinate
		batSpeed,
		ballSpeed = getBall()->getSpeed();

	const GameEngine::Coordinate* ballPosition = getBallPosition(ballSpeed, player);
	uint8_t batLimit = MAX_BAT_SPEED - ballSpeed.getZ();

	batSpeed = (*batPosition) - (*ballPosition);
	if (abs(batSpeed.getX()) > batLimit) {
		batSpeed.setX(batSpeed.getX() < 0 ? -batLimit : batLimit);
	}

	if (abs(batSpeed.getY()) > batLimit) {
		batSpeed.setY(batSpeed.getY() < 0 ? -batLimit : batLimit);
	}

	batSpeed.setZ(0);

	return batSpeed;
}

void Demo::moveBat() {
	uint8_t player = getBall()->getPosition().getZ() < 40 ? 1 : 2;
	const GameEngine::Coordinate *batPosition = &getBats()[player]->getPosition();

	GameEngine::Coordinate batSpeed = calcBatSpeed(player, batPosition);
	GameEngine::Coordinate batNewPosition = calcBatNewPosition(batPosition, batSpeed);
	getBats()[player]->setPosition(batNewPosition);

	if (getBats()[player + 2] != nullptr){
		getBats()[player + 2]->setPosition(batNewPosition);
	}
}

void Demo::updateLimits() {
	GameEngine::Coordinate ballSpeed = ballSpeed = getBall()->getSpeed();
	const GameEngine::Coordinate* ballPosition = &getBall()->getPosition();

	if (ballPosition->getZ() == 71 || ballPosition->getZ() == 9) {
		if (m_counter++ == 7) {
			m_counter = 0;
			if (ballSpeed.getZ() < 0) {
				getBall()->setSpeed(GameEngine::Coordinate(
								ballSpeed.getX(),
								ballSpeed.getY(),
								ballSpeed.getZ() - 1
				));
			} else {
				getBall()->setSpeed(GameEngine::Coordinate(
						ballSpeed.getX(),
						ballSpeed.getY(),
						ballSpeed.getZ() + 1
				));
			}
		}
	}
}

void Demo::onNotify() {
	GameController::onNotify();
	moveBat();
	updateLimits();
}

} /* namespace GameControllers */
