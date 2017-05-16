/*
 * Tennis.cpp
 *
 *  Created on: 15 mei 2017
 *      Author: Acer
 */

#include <GameControllers/Tennis.h>
#include <gameEngine/Coordinate.h>
#include <gameEngine/Ball.h>

namespace GameControllers {

Tennis::Tennis(GameEngine::Ball *ball)
	: GameController(ball)
{
}

Tennis::~Tennis() {

}

void Tennis::onNotify() {
	GameEngine::Coordinate *speed;
	const GameEngine::Coordinate *ballCoordinage = &getBall()->getPosition();

	GameController::onNotify();

	if (ballCoordinage->getZ() > 72 || ballCoordinage->getZ() < 8){
		getBall()->setPosition(GameEngine::Coordinate(ballCoordinage->getX(), ballCoordinage->getY(), 40));
		speed = &getBall()->getSpeed();
//		speed->flip(GameEngine::Coordinate::X);
//		speed->flip(GameEngine::Coordinate::Y);
		speed->flip(GameEngine::Coordinate::Z);

		winMatch();
	}
}

} /* namespace GameControllers */
