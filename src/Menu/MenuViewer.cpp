/*
 * MenuViewer.cpp
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */
#include <Menu/MenuViewer.h>
#include <config_file.h>
#include <Menu/MenuBox.h>
#include <Menu/MenuItem.h>
#include <Menu/TextManager.h>
#include <GameControllers/GameController.h>
#include <FPGA.h>
#include <Game.h>

#define MENU_CENTER				39
#define MENU_WIDTH				16
#define BORDER_LEFT				MENU_CENTER - MENU_WIDTH / 2
#define BORDER_RIGHT			MENU_CENTER + MENU_WIDTH / 2
#define MENU_TOP				3
#define TITLE_COLOR				0xF22
#define SELECTED_COLOR			0xFA0
#define ITEM_COLOR				0x0F0
#define FOOTER_AND_HEADER_COLOR 0xFFF
#define SHIFT_RED				0
#define SHIFT_GREEN				4
#define SHIFT_BLUE				8
#define ANIMATION_DELAY			2

namespace Menu {

MenuViewer::MenuViewer(MenuBox *menu)
	: MVC::View(menu)
	, m_lastSelected(1)
	, m_animationDelay(0)
	, m_animationColor(ITEM_COLOR)
{
}

MenuViewer::~MenuViewer() {

}

void MenuViewer::drawChild(const MenuItem* child, bool selected) {
	uint8_t  amountSpace = MENU_WIDTH/2 - child->getTitle().length() / 2;
	TextManager::setColumn(BORDER_LEFT - 1);
	if (selected) {
		TextManager::print(" >");
	} else {
		TextManager::print("  ");
	}

	TextManager::print(std::string(amountSpace, ' '));
	TextManager::print(child->getTitle());
	amountSpace -= 1;
	TextManager::print(std::string(amountSpace, ' '));

	if (selected) {
		TextManager::print("< ");
	} else {
		TextManager::print("  ");
	}
}

void MenuViewer::drawMenu(MenuBox* menu) {
	MenuItem *parent = menu->getCurrentMenu();
	uint8_t i, amountSpace = MENU_WIDTH/2 - parent->getTitle().length() / 2;;

	if (!parent->hasChilds()) return;

	TextManager::setLine(MENU_TOP);
	TextManager::setColor(TITLE_COLOR);


	TextManager::setColumn(MENU_CENTER - MENU_WIDTH/2);
	TextManager::print(std::string(amountSpace, ' '));
	TextManager::print(parent->getTitle());
	amountSpace -= 1;
	TextManager::print(std::string(amountSpace, ' '));

	TextManager::setColor(ITEM_COLOR);
	for (i = 0; i < 10; ++i) {
		TextManager::setLine(5 + i);
		if (i < parent->amountOfChilds()){
			if (i == menu->getSelected()){
				TextManager::setColor(m_animationColor);

				drawChild((*parent)[i], true);

				TextManager::setColor(ITEM_COLOR);
			} else {
				drawChild((*parent)[i], false);
			}
		} else {
			TextManager::setColumn(BORDER_LEFT - 1);
			TextManager::print(std::string(MENU_WIDTH * 2 + 1, ' '));
		}
	}
}

void MenuViewer::drawFooter() {
	TextManager::setLine(29);
	TextManager::setColumn(0);
	TextManager::print(" Made by Verney,Rick,Pip,Tom,Jenny & David (Avans Hogeschool, s'Hertogenbosch)");
}

void MenuViewer::drawTop() {
	TextManager::setLine(0);
	TextManager::setColumn(0);
	TextManager::print(" Please, take a controller and play!");
	TextManager::setColumn(63);
	TextManager::print(PROGRAM_VERSION);
}

void MenuViewer::animateColor(uint8_t shifter) {

	int8_t
		difference 	= ((int8_t)SELECTED_COLOR >> shifter) - ((int8_t)m_animationColor >> shifter),
		color		= m_animationColor >> shifter;
	int16_t filter = 0x0F << shifter;
	if (difference < 0) {
		color += 1;
	} else if (difference > 0) {
		color -= 1;
	}

	m_animationColor = (m_animationColor & ~filter) | (color << shifter);
}

void MenuViewer::animate() {
	MenuBox *menu = (MenuBox *)getModel();

	if (!menu->isShowing() || m_animationDelay--)
		return;
	m_animationDelay = ANIMATION_DELAY;

	if (m_lastSelected != menu->getSelected()) {
		m_lastSelected = menu->getSelected();
		m_animationColor = ITEM_COLOR;
	} else {
		animateColor(SHIFT_RED);
		animateColor(SHIFT_GREEN);
		animateColor(SHIFT_BLUE);
	}

	TextManager::setColor(m_animationColor);
	TextManager::setLine(5 + menu->getSelected());
	drawChild((*menu->getCurrentMenu())[menu->getSelected()], true);
	TextManager::setColor(ITEM_COLOR);
}

void MenuViewer::onNotify() {
	FPGA *fpga = FPGA::getInstance();
	uint16_t fpgaOptions = fpga->getOptions();
	MenuBox *menu = (MenuBox *)getModel();
	resetNotifyFlag();

	animate();

	if (menu->isShowing()){
		if ((fpgaOptions & FPGA_OPTION_MENU) != FPGA_OPTION_MENU){
			fpgaOptions |= FPGA_OPTION_MENU;
			fpga->setOption(fpgaOptions);
			TextManager::clearAll();

			TextManager::setColor(FOOTER_AND_HEADER_COLOR);
			drawTop();
			drawFooter();
		}
		drawMenu(menu);
	} else if (!menu->isShowing() && (fpgaOptions & FPGA_OPTION_MENU) == FPGA_OPTION_MENU) {
		fpgaOptions &= ~FPGA_OPTION_MENU;
		fpga->setOption(fpgaOptions);
		TextManager::clearAll();
		Game::getInstance()->getCurrentController()->play();
	}
}

} /* namespace Menu */
