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
#include <FPGA.h>

#include <Menu/TextManager.h>

namespace GameControllers {

Tennis::Tennis(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2)
	: GameController(ball, player1, player2)
{
}

Tennis::~Tennis() {

}

void Tennis::onNotify() {
	GameController::onNotify();
	uint8_t player;
	GameEngine::GameObject *bat;// = getBats()[GAMECONTROLLER_BAT1_PLAYER1];
	GameEngine::Coordinate positionPlayer;//1 = getPlayer(1)->getPosition();

	for (player = 1; player < 3; ++player) {
		bat = getBats()[player];
		positionPlayer = getPlayer(player)->getPosition();

		positionPlayer.setX(positionPlayer.getX() - bat->getWidth() / 2);
		positionPlayer.setY(positionPlayer.getY() - bat->getHeight() / 2);

		bat->setPosition(positionPlayer);
		Menu::TextManager::setLine(0);
		Menu::TextManager::setColumn(0);
		Menu::TextManager::print("(" +
				Menu::TextManager::to_string(bat->getPosition().getX()) + ", " +
				Menu::TextManager::to_string(bat->getPosition().getY()) + ")"
		);
	}

	if (getFpga() != nullptr){
		getFpga()->update(FPGA_UPDATE_P1);
		getFpga()->update(FPGA_UPDATE_P2);
	}
}

} /* namespace GameControllers */
