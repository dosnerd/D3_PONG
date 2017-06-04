/*
 * StartHockey.cpp
 *
 *  Created on: 4 jun. 2017
 *      Author: Acer
 */

#include <Menu/MenuItems/StartHockey.h>
#include <GameControllers/Hockey.h>
#include <gameEngine/Engine.h>
#include <FPGA.h>
#include <Game.h>

namespace Menu {
namespace MenuItems {

StartHockey::StartHockey(MenuItem * parent)
	: MenuItem("Hockey", parent)
{
}

StartHockey::~StartHockey() {
}

void StartHockey::select() {
	Game *game = Game::getInstance();

	game->setEngine(new GameEngine::Engine());

	GameControllers::Hockey *controller = new GameControllers::Hockey(game->getEngine()->getBall(), game->getPlayer(1), game->getPlayer(2));
	Game::getInstance()->setGameController(controller);

	controller->bind(FPGA::getInstance());
	controller->setupField(game->getEngine());
}

} /* namespace MenuItems */
} /* namespace Menu */
