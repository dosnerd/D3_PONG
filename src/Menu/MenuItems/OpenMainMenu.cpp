/*
 * OpenMainMenu.cpp
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#include <Menu/MenuItems/OpenMainMenu.h>
#include <Game.h>

namespace Menu {
namespace MenuItems {

OpenMainMenu::OpenMainMenu(MenuItem *parent)
	: MenuItem("Main Menu", parent)
{

}

OpenMainMenu::~OpenMainMenu() {

}

void OpenMainMenu::select() {
	Game::getInstance()->openMainMenu();
}

} /* namespace MenuItems */
} /* namespace Menu */
