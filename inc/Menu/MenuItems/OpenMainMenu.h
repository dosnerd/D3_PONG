/*
 * OpenMainMenu.h
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEMS_OPENMAINMENU_H_
#define INC_MENU_MENUITEMS_OPENMAINMENU_H_

#include <Menu/MenuItem.h>

namespace Menu {
namespace MenuItems {

class OpenMainMenu: public MenuItem {
public:
								OpenMainMenu(MenuItem *parent);
	virtual 					~OpenMainMenu();

public:
	virtual void				select();
};

} /* namespace MenuItems */
} /* namespace Menu */

#endif /* INC_MENU_MENUITEMS_OPENMAINMENU_H_ */
