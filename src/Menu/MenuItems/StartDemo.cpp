/*
 * StartDemo.cpp
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#include <Menu/MenuItems/StartDemo.h>
#include <GameControllers/Demo.h>
#include <gameEngine/Engine.h>
#include <FPGA.h>
#include <Game.h>

namespace Menu {
	namespace MenuItems {

	StartDemo::StartDemo(Menu::MenuItem *parent)
		: Menu::MenuItem("Demo", parent)
	{

	}

	StartDemo::~StartDemo() {

	}

	void StartDemo::select() {
		Game *game = Game::getInstance();

		game->setEngine(new GameEngine::Engine());

		GameControllers::Demo *controller = new GameControllers::Demo(game->getEngine()->getBall(), game->getPlayer(1), game->getPlayer(2));
		Game::getInstance()->setGameController(controller);

		controller->bind(FPGA::getInstance());
		controller->setupField(game->getEngine());
	}

} /* namespace MenuItems */
} /* namespace Menu */
