/*
 * MainMenu.cpp
 *
 *  Created on: 29 mei 2017
 *      Author: Acer
 */

#include <Menu/MainMenu.h>
#include <Menu/TextManager.h>

namespace Menu {

MainMenu::MainMenu()
	: m_selected(0)
{

}

MainMenu::~MainMenu() {

}

void MainMenu::print() {
	uint8_t i;
	TextManager::setLine(4);
	TextManager::setColumn(40 - 5);
	TextManager::setColor(0xF00);
	TextManager::printLine("MAIN MENU ");

	TextManager::setColor(0x0F0);
	for (i = 0; i < 4; ++i) {
		TextManager::setLine(6 + i);
		printItem(i, i == m_selected);
	}
}

void MainMenu::select() {
}

void MainMenu::up() {
	if (m_selected == 0)
		m_selected = 3;
	else
		m_selected--;
}

void MainMenu::down() {
	if (m_selected == 3)
		m_selected = 0;
	else
		m_selected++;
}

void MainMenu::printItem(uint8_t item, bool selected) {
	std::string buffer;
	uint8_t column = 8;
	switch (item){
	case 0:
		buffer = "Demo";
		break;
	case 1:
		buffer = "Tennis";
		break;
	case 2:
		buffer = "Hockey";
		break;
	case 3:
		buffer = "Handball";
		break;
	}

	TextManager::setColumn(39 - column);
	if (selected){
		TextManager::print(">");
		TextManager::setColumn(40 - buffer.length() / 2);
		TextManager::print(buffer);
		TextManager::setColumn(39 + column);
		TextManager::printLine("<");
	} else {
		TextManager::print(" ");
		TextManager::setColumn(40 - buffer.length() / 2);
		TextManager::print(buffer);
		TextManager::setColumn(39 + column);
		TextManager::printLine(" ");
	}
}

} /* namespace Menu */
