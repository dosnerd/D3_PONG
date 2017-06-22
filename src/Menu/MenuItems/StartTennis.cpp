/*
 * StartTennis.cpp
 *
 *  Created on: 1 jun. 2017
 *      Author: Acer
 */

#include <Menu/MenuItems/StartTennis.h>
#include <Game.h>
#include <FPGA.h>
#include <GameControllers/Tennis.h>
#include <gameEngine/Engine.h>

namespace Menu {
namespace MenuItems {

StartTennis::StartTennis(Menu::MenuItem *parent)
	: Menu::MenuItem("Tennis", parent)
{
}

StartTennis::~StartTennis() {
}

void StartTennis::select() {
	Game *game = Game::getInstance();

	game->setEngine(new GameEngine::Engine());

	GameControllers::Tennis *controller = new GameControllers::Tennis(game->getEngine()->getBall(), game->getPlayer(1), game->getPlayer(2));
	Game::getInstance()->setGameController(controller);

	controller->bind(FPGA::getInstance());
	controller->setupField(game->getEngine());
}

} /* namespace MenuItems */
} /* namespace Menu */
