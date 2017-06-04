/*
 * Hockey.cpp
 *
 *  Created on: 4 jun. 2017
 *      Author: Acer
 */

#include <GameControllers/Hockey.h>
#include <FPGA.h>
#include <gameEngine/GameObject.h>
#include <gameEngine/Engine.h>
#include <GameControllers/PlayerController.h>
#include <config_file.h>

namespace GameControllers {

Hockey::Hockey(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2)
	: GameController(ball, player1, player2)
{
}

Hockey::~Hockey() {
}

void Hockey::setupField(GameEngine::Engine* engine) {
	GameController::setupField(engine);


	getBats()[GAMECONTROLLER_BAT2_PLAYER1] = new GameEngine::GameObject(GameEngine::Coordinate::Z, BAT_WITDH, BAT_HEIGHT);
	getBats()[GAMECONTROLLER_BAT2_PLAYER2] = new GameEngine::GameObject(GameEngine::Coordinate::Z, BAT_WITDH, BAT_HEIGHT);

	getBats()[GAMECONTROLLER_BAT2_PLAYER1]->setPosition(GameEngine::Coordinate(-BAT_WITDH/2, -BAT_HEIGHT/2, 32));
	getBats()[GAMECONTROLLER_BAT2_PLAYER2]->setPosition(GameEngine::Coordinate(-BAT_WITDH/2, -BAT_HEIGHT/2, 48));

	engine->addObject(getBats()[GAMECONTROLLER_BAT2_PLAYER1]);
	engine->addObject(getBats()[GAMECONTROLLER_BAT2_PLAYER2]);

	if (getFpga() != nullptr){
		getFpga()->setOption(FPGA_OPTION_HOCKEY_MODE | (getFpga()->getOptions() & FPGA_OPTION_MENU));
		getFpga()->update(FPGA_UPDATE_ALL);
	}

}

void Hockey::onNotify() {

	GameController::onNotify();
	uint8_t player;
	GameEngine::GameObject *bat;
	GameEngine::Coordinate positionPlayer;


	for (player = 1; player < 3; ++player) {
		bat = getBats()[player];
		positionPlayer = getPlayer(player)->getPosition();

		positionPlayer.setX(0);
		positionPlayer.setY(0);
		positionPlayer.setX(positionPlayer.getX() - bat->getWidth() / 2);
		positionPlayer.setY(positionPlayer.getY() - bat->getHeight() / 2);
		positionPlayer.setZ(bat->getPosition().getZ());

		bat->setPosition(positionPlayer);
		bat = getBats()[player + 2];
		positionPlayer.setZ(bat->getPosition().getZ());
		bat->setPosition(positionPlayer);
	}

	if (getFpga() != nullptr){
		getFpga()->update(FPGA_UPDATE_P1);
		getFpga()->update(FPGA_UPDATE_P2);
	}
}

} /* namespace GameControllers */
