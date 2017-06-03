/*
 * SetInfrared.h
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEMS_SETINFRARED_H_
#define INC_MENU_MENUITEMS_SETINFRARED_H_

#include <Menu/MenuItem.h>

namespace Menu {
namespace MenuItems {

class SetInfrared: public MenuItem {
public:
								SetInfrared(MenuItem * parent);
	virtual 					~SetInfrared();

public:
	void						select();
};

} /* namespace MenuItems */
} /* namespace Menu */

#endif /* INC_MENU_MENUITEMS_SETINFRARED_H_ */
