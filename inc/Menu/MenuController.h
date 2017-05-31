/*
 * MenuController.h
 *
 *  Created on: 29 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUCONTROLLER_H_
#define INC_MENU_MENUCONTROLLER_H_

#include <Menu/Menu.h>

namespace Menu {

class MenuController {
public:
								MenuController();
	virtual 					~MenuController();

public:
	void						show(Menu *menu);
	void						hide();
	void						print();
	bool						isShowing();
	
	static MenuController		*getInstance();

private:
	static MenuController		sInstance;
	Menu						*m_menu;

	void						printStandard();
};

} /* namespace Menu */

#endif /* INC_MENU_MENUCONTROLLER_H_ */
