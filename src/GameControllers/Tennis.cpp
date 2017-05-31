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

Tennis::Tennis(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2)
	: GameController(ball, player1, player2)
{
}

Tennis::~Tennis() {

}

void Tennis::onNotify() {
	GameController::onNotify();
}

} /* namespace GameControllers */
