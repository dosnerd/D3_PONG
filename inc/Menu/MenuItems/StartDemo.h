/*
 * StartDemo.h
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEMS_STARTDEMO_H_
#define INC_MENU_MENUITEMS_STARTDEMO_H_

#include <Menu/MenuItem.h>

namespace Menu {
	namespace MenuItems {

	class StartDemo: public Menu::MenuItem {
	public:
									StartDemo(Menu::MenuItem *parent);
		virtual 					~StartDemo();

		virtual void				select();
	};

	} /* namespace MenuItems */
} /* namespace Menu */
#endif /* INC_MENU_MENUITEMS_STARTDEMO_H_ */
