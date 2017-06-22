/*
 * ContinueGame.h
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEMS_RESUMEGAME_H_
#define INC_MENU_MENUITEMS_RESUMEGAME_H_

#include <Menu/MenuItem.h>

namespace Menu {
namespace MenuItems {

class ResumeGame: public MenuItem {
public:
								ResumeGame(MenuItem *parent);
	virtual 					~ResumeGame();

public:
	virtual void				select();
};

} /* namespace MenuItems */
} /* namespace Menu */

#endif /* INC_MENU_MENUITEMS_RESUMEGAME_H_ */
