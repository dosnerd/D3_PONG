/*
 * ContinueGame.cpp
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#include <Game.h>
#include <Menu/MenuItems/ResumeGame.h>

namespace Menu {
namespace MenuItems {

ResumeGame::ResumeGame(MenuItem *parent)
	: MenuItem("Resume game", parent)
{
}

ResumeGame::~ResumeGame() {

}

void ResumeGame::select() {
	Game::getInstance()->resume();
}

} /* namespace MenuItems */
} /* namespace Menu */
