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

namespace GameControllers {

Demo::Demo(GameEngine::Ball *ball)
	: GameController(ball)
{
	// TODO Auto-generated constructor stub

}

Demo::~Demo() {
	// TODO Auto-generated destructor stub
}

void Demo::onNotify() {
	GameController::onNotify();

	GameEngine::Coordinate *speed, batToBall;
	const GameEngine::Coordinate
			*batCoordinate,
			*ballCoordinate = &getBall()->getPosition();
	uint8_t player = ballCoordinate->getZ() < 40 ? 1 : 2;
	batCoordinate = &getBat(player)->getPosition(),

	batToBall = (*batCoordinate) - (*ballCoordinate);
	if (abs(batToBall.getX()) > 10){
		batToBall.setX(batToBall.getX() < 0 ? -10 : 10);
	}
	if (abs(batToBall.getY()) > 10){
		batToBall.setY(batToBall.getY() < 0 ? -10 : 10);
	}

	batToBall.setZ(0);

	batToBall = (*batCoordinate) - batToBall;
	if (abs(batToBall.getX() ) > 420){
		batToBall.setX(batToBall.getX() < 0 ? -420 : 420);
	}
	if (abs(batToBall.getY()) > 240){
		batToBall.setY(batToBall.getY() < 0 ? -240 : 240);
	}


	getBat(player)->setPosition(batToBall);


	if (ballCoordinate->getZ() > 72 || ballCoordinate->getZ() < 8){
		getBall()->setPosition(GameEngine::Coordinate(ballCoordinate->getX(), ballCoordinate->getY(), 40));
		speed = &getBall()->getSpeed();
		speed->flip(GameEngine::Coordinate::Z);

		winMatch();
	}
}

} /* namespace GameControllers */
