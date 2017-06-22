/*
 * StartHandball.cpp
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#include <Menu/MenuItems/StartHandball.h>
#include <GameControllers/Handball.h>
#include <Game.h>
#include <gameEngine/Engine.h>
#include <FPGA.h>

namespace Menu {
namespace MenuItems {

StartHandball::StartHandball(MenuItem *parent)
	: Menu::MenuItem("Handball", parent)
{


}

StartHandball::~StartHandball()
{

}

void StartHandball::select() {
	Game *game = Game::getInstance();

	game->setEngine(new GameEngine::Engine());

	GameControllers::Handball *controller = new GameControllers::Handball(game->getEngine()->getBall(), game->getPlayer(1), game->getPlayer(2));
	Game::getInstance()->setGameController(controller);

	controller->bind(FPGA::getInstance());
	controller->setupField(game->getEngine());

}

} /* namespace MenuItems */
} /* namespace Menu */
