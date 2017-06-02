/*
 * MenuBox.cpp
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#include <Menu/MenuBox.h>
#include <Menu/MenuItem.h>

namespace Menu {

MenuBox MenuBox::sInstance;
MenuBox::MenuBox()
	: m_iCurrent(0)
	, m_current(nullptr)
{
}

MenuBox::~MenuBox() {
}

void MenuBox::show(MenuItem* item) {
	if (item->hasChilds()){
		m_current = item;
	} else {
		m_current = nullptr;
		item->select();
	}
	m_iCurrent = 0;
	notifyObservers();
}

void MenuBox::hide() {
	m_current = nullptr;
	m_iCurrent = 0;
	notifyObservers();
}

void MenuBox::up() {
	if (isShowing()){
		if (m_iCurrent == 0){
			m_iCurrent = m_current->amountOfChilds() - 1;
		} else {
			m_iCurrent--;
		}

		notifyObservers();
	}
}

void MenuBox::down() {
	if (isShowing()){
		if (++m_iCurrent >= m_current->amountOfChilds()){
			m_iCurrent = 0;
		}

		notifyObservers();
	}
}

void MenuBox::goTo(uint8_t child) {
	if (isShowing()){
		if (child < m_current->amountOfChilds()){
			m_iCurrent = child;
			notifyObservers();
		}
	}
}

bool MenuBox::isShowing() {
	return m_current != nullptr;
}

const uint8_t& MenuBox::getSelected() const {
	return m_iCurrent;
}

MenuItem* MenuBox::getCurrentMenu() {
	return m_current;
}

MenuBox* Menu::MenuBox::getInstance() {
	return &sInstance;
}

void Menu::MenuBox::select() {
	MenuItem *tmp;
	uint8_t selected;
	if (isShowing()){
		if ((*m_current)[m_iCurrent]->hasChilds()){
			show((*m_current)[m_iCurrent]);
		}
		else{
			tmp = m_current;
			selected = m_iCurrent;
			hide();
			(*tmp)[selected]->select();
		}
	}
}

} /* namespace Menu */
