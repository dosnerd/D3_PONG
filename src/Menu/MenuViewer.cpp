/*
 * MenuViewer.cpp
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */
#include <config_file.h>
#include <Menu/MenuViewer.h>
#include <Menu/MenuBox.h>
#include <Menu/MenuItem.h>
#include <Menu/TextManager.h>
#include <GameControllers/GameController.h>
#include <FPGA.h>
#include <Game.h>

#define MENU_CENTER		39
#define MENU_WIDTH		16
#define BORDER_LEFT		MENU_CENTER - MENU_WIDTH / 2
#define BORDER_RIGHT	MENU_CENTER + MENU_WIDTH / 2
#define MENU_TOP		3
#define TITLE_COLOR		0xF00
#define SELECTED_COLOR	0x7F7
#define ITEM_COLOR		0x0F0

namespace Menu {

MenuViewer::MenuViewer(MenuBox *menu)
	: MVC::View(menu)
{
}

MenuViewer::~MenuViewer() {

}

void MenuViewer::drawChild(const MenuItem* child, bool selected) {
	uint8_t  amountSpace = MENU_WIDTH/2 - child->getTitle().length() / 2;
	TextManager::setColumn(BORDER_LEFT);
	if (selected) {
		TextManager::print(">");
	} else {
		TextManager::print(" ");
	}

	TextManager::print(std::string(amountSpace, ' '));
	TextManager::print(child->getTitle());
	amountSpace -= 1;
	TextManager::print(std::string(amountSpace, ' '));

	if (selected) {
		TextManager::print("<");
	} else {
		TextManager::print(" ");
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
	for (i = 0; i < parent->amountOfChilds(); ++i) {
		TextManager::setLine(5 + i);
		if (i == menu->getSelected()){
			TextManager::setColor(SELECTED_COLOR);

			drawChild((*parent)[i], true);

			TextManager::setColor(ITEM_COLOR);
		} else {
			drawChild((*parent)[i], false);
		}
	}
}

void MenuViewer::drawFooter() {
	TextManager::setLine(29);
	TextManager::setColumn(0);
	TextManager::setColor(0xFFF);
	TextManager::print(" Made by Verney,Rick,Pip,Tom,Jenny & David (Avans Hogeschool, s'Hertogenbosch)");
}

void MenuViewer::drawTop() {
	TextManager::setLine(0);
	TextManager::setColumn(63);
	TextManager::setColor(0xFFF);
	TextManager::print(PROGRAM_VERSION);
}

void MenuViewer::onNotify() {
	FPGA *fpga = FPGA::getInstance();
	uint16_t fpgaOptions = fpga->getOptions();
	MenuBox *menu = (MenuBox *)getModel();
	resetNotifyFlag();

	if (menu->isShowing()){
		if ((fpgaOptions & FPGA_OPTION_MENU) != FPGA_OPTION_MENU){
			fpgaOptions |= FPGA_OPTION_MENU;
			fpga->setOption(fpgaOptions);
			TextManager::clearAll();
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
