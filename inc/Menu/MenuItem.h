/*
 * MenuItem.h
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEM_H_
#define INC_MENU_MENUITEM_H_

#include <Vector.h>
#include <string>

namespace Menu {

class MenuItem {
public:
								MenuItem(std::string title, MenuItem *parent = nullptr);
	virtual 					~MenuItem();

	virtual MenuItem			*operator[](uint8_t child);

public:
	virtual void				select();
	virtual void				addChild(MenuItem *child);
	virtual const bool			hasChilds() const;
	virtual const uint8_t		amountOfChilds() const;
	virtual const std::string	&getTitle() const;

public:
	virtual MenuItem			*getParent();

private:
	std::string					m_title;
	Vector<MenuItem *>			m_childs;
	MenuItem					*m_pParent;
};

} /* namespace Menu */

#endif /* INC_MENU_MENUITEM_H_ */
