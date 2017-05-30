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
	TextManager::printLine("MAIN MENU ");

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

	TextManager::setColumn(40 - buffer.length() / 2 - 1);
	if (selected){
		TextManager::print(">");
		TextManager::print(buffer);
		TextManager::printLine("<");
	} else {
		TextManager::print(" ");
		TextManager::print(buffer);
		TextManager::printLine(" ");
	}
}

} /* namespace Menu */
