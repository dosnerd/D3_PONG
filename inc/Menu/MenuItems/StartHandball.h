/*
 * StartHandball.h
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEMS_STARTHANDBALL_H_
#define INC_MENU_MENUITEMS_STARTHANDBALL_H_

#include <Menu/MenuItem.h>

namespace Menu {
namespace MenuItems {

class StartHandball : public MenuItem {
public:
								StartHandball(MenuItem *parent);
	virtual 					~StartHandball();

public:
	virtual void				select();
};

} /* namespace MenuItems */
} /* namespace Menu */

#endif /* INC_MENU_MENUITEMS_STARTHANDBALL_H_ */
