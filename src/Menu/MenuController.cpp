/*
 * MenuController.cpp
 *
 *  Created on: 29 mei 2017
 *      Author: Acer
 */

#include <Menu/MenuController.h>
#include <Menu/TextManager.h>

namespace Menu {

MenuController MenuController::sInstance;
MenuController::MenuController()
	: m_menu(nullptr)
{
}

MenuController::~MenuController() {
}

void MenuController::show(Menu* menu) {
	m_menu = menu;
	printStandard();
	print();
}

void MenuController::hide() {
	m_menu = nullptr;
	TextManager::clearAll();
	printStandard();
}

void MenuController::print() {
	if (m_menu != nullptr){
		m_menu->print();
	}
}

MenuController* MenuController::getInstance() {
	return &sInstance;
}

void MenuController::printStandard() {
	TextManager::setColumn(63);
	TextManager::printLine("Version: 0.5.31");
	TextManager::setLine(29);
	TextManager::print("Made by Verney, Rick, Pip, Tom, Jenny & David at Avans Hogeschool at Den Bosch");
	TextManager::setLine(1);
}

} /* namespace Menu */
