/*
 * PlayerColorSelect.h
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUITEMS_PLAYERCOLORSELECT_H_
#define INC_MENU_MENUITEMS_PLAYERCOLORSELECT_H_

#include <Menu/MenuItem.h>

namespace Menu {
namespace MenuItems {

class PlayerColorSelect: public MenuItem {
public:
									PlayerColorSelect(MenuItem *parent, uint8_t player, uint16_t color);
	virtual 						~PlayerColorSelect();

public:
	virtual void					select();

private:
	uint8_t 						m_player;
	uint16_t						m_color;
};

} /* namespace MenuItems */
} /* namespace Menu */

#endif /* INC_MENU_MENUITEMS_PLAYERCOLORSELECT_H_ */
