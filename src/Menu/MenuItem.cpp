/*
 * MenuItem.cpp
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#include <Menu/MenuItem.h>

namespace Menu {

MenuItem::MenuItem(std::string title, MenuItem *parent)
	: m_title(title)
	, m_pParent(parent)
{

}

MenuItem::~MenuItem() {
}

void MenuItem::select() { }

const bool MenuItem::hasChilds() const {
	return m_childs.length() > 0;
}

void MenuItem::addChild(MenuItem* child) {
	m_childs.add(child);
}

MenuItem* MenuItem::operator [](uint8_t child) {
	if (child < m_childs.length()){
		return m_childs[child];
	}

	return nullptr;
}

const uint8_t MenuItem::amountOfChilds() const {
	return m_childs.length();
}

const std::string& MenuItem::getTitle() const {
	return m_title;
}

MenuItem* Menu::MenuItem::getParent() {
	return m_pParent;
}

void Menu::MenuItem::setTitle(std::string title) {
	m_title = title;
}

} /* namespace Menu */
