/*
 * MainMenu.h
 *
 *  Created on: 29 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MAINMENU_H_
#define INC_MENU_MAINMENU_H_

#include <Menu/Menu.h>
#include <stdint.h>

namespace Menu {

class MainMenu: public Menu {
public:
								MainMenu();
	virtual 					~MainMenu();

public:
	virtual void				print();
	virtual void				select();
	virtual void				up();
	virtual void				down();

private:
	uint8_t						m_selected;

	void						printItem(uint8_t item, bool selected);
};

} /* namespace Menu */

#endif /* INC_MENU_MAINMENU_H_ */
