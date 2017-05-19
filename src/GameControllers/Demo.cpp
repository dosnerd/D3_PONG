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
	, m_counter(0)
	, m_limit(10)
{
}

Demo::~Demo() {
}

void Demo::onNotify() {
	if (getBall()->getPosition().getZ() > 72 || getBall()->getPosition().getZ() < 8){
		m_limit = 10;
		getBall()->setSpeed(GameEngine::Coordinate(5, -3, 	1));
	}
	GameController::onNotify();

	GameEngine::Coordinate ballSpeed, batToBall, center(-getBat(1)->getWidth()/2,-getBat(1)->getHeight()/2,0);
	const GameEngine::Coordinate
			*batCoordinate,
			*ballCoordinate = &getBall()->getPosition();
	uint8_t player = ballCoordinate->getZ() < 40 ? 1 : 2;
	batCoordinate = &getBat(player)->getPosition();


	if (getBall()->getSpeed().getZ() > 0 && player == 1){
		ballCoordinate = &center;
	} else if (getBall()->getSpeed().getZ() < 0 && player == 2) {
		ballCoordinate = &center;
	}

	batToBall = (*batCoordinate) - (*ballCoordinate);
	if (abs(batToBall.getX()) > m_limit){
		batToBall.setX(batToBall.getX() < 0 ? -m_limit : m_limit);
	}
	if (abs(batToBall.getY()) > m_limit){
		batToBall.setY(batToBall.getY() < 0 ? -m_limit : m_limit);
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
	if (ballCoordinate->getZ() == 71 || ballCoordinate->getZ() == 9){
		if (m_counter++ & 0x4){
			m_counter=0;
			if (m_limit != 1) m_limit-=2;
			ballSpeed = getBall()->getSpeed();

			if (ballSpeed.getZ() < 0){
				getBall()->setSpeed(GameEngine::Coordinate(ballSpeed.getX(), ballSpeed.getY(), -6+(m_limit/2)));
			}
			else{
				getBall()->setSpeed(GameEngine::Coordinate(ballSpeed.getX(), ballSpeed.getY(), 6-(m_limit/2)));
			}
		}
	}
}

} /* namespace GameControllers */
