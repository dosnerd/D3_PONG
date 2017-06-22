/*
 * StartHockey.h
 *
 *  Created on: 4 jun. 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEMS_STARTHOCKEY_H_
#define INC_MENU_MENUITEMS_STARTHOCKEY_H_

#include <Menu/MenuItem.h>

namespace Menu {
namespace MenuItems {

class StartHockey: public MenuItem {
public:
								StartHockey(MenuItem * parent);
	virtual 					~StartHockey();

public:
	virtual void				select();
};

} /* namespace MenuItems */
} /* namespace Menu */

#endif /* INC_MENU_MENUITEMS_STARTHOCKEY_H_ */
