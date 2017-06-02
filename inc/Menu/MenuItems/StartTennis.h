/*
 * StartTennis.h
 *
 *  Created on: 1 jun. 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEMS_STARTTENNIS_H_
#define INC_MENU_MENUITEMS_STARTTENNIS_H_

#include <Menu/MenuItem.h>

namespace Menu {
	namespace MenuItems {

	class StartTennis: public MenuItem {
	public:
									StartTennis(Menu::MenuItem *parent);
		virtual 					~StartTennis();

	public:
		virtual void				select();
	};

	} /* namespace MenuItems */
} /* namespace Menu */

#endif /* INC_MENU_MENUITEMS_STARTTENNIS_H_ */
