/*
 * PlayerColorSelect.cpp
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#include <Menu/MenuItems/PlayerColorSelect.h>
#include <Menu/TextManager.h>
#include <Menu/MenuBox.h>
#include <Game.h>
#include <FPGA.h>

namespace Menu {
namespace MenuItems {

PlayerColorSelect::PlayerColorSelect(MenuItem *parent, uint8_t player, uint16_t color)
	: MenuItem("x" + Menu::TextManager::to_string((int16_t)color, true), parent)
	, m_player(player)
	, m_color(color)
{

}

PlayerColorSelect::~PlayerColorSelect()
{
}

void PlayerColorSelect::select() {
	Game::getInstance()->getPlayer(m_player)->setColor(m_color);
	if (m_player == 1)
		FPGA::getInstance()->setRegister(FPGA_REGISTER_COLOR_PLAYER1, m_color);
	else
		FPGA::getInstance()->setRegister(FPGA_REGISTER_COLOR_PLAYER2, m_color);

	Menu::MenuBox::getInstance()->show(getParent()->getParent());
}

} /* namespace MenuItems */
} /* namespace Menu */
