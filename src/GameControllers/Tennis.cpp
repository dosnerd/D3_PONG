/*
 * Tennis.cpp
 *
 *  Created on: 15 mei 2017
 *      Author: Acer
 */

#include <GameControllers/Tennis.h>
#include <gameEngine/Coordinate.h>
#include <gameEngine/Ball.h>
#include <GameControllers/PlayerController.h>

namespace GameControllers {

Tennis::Tennis(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2)
	: GameController(ball, player1, player2)
{
}

Tennis::~Tennis() {

}

void Tennis::onNotify() {
	GameController::onNotify();
	GameEngine::GameObject *bat = getBats()[GAMECONTROLLER_BAT1_PLAYER1];
	GameEngine::Coordinate positionPlayer1 = getPlayer(1)->getPosition();
	positionPlayer1.setX(positionPlayer1.getX() - bat->getWidth() / 2);
	positionPlayer1.setY(positionPlayer1.getY() - bat->getHeight() / 2);
	bat->setPosition(positionPlayer1);
}

} /* namespace GameControllers */
