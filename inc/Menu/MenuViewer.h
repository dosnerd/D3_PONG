/*
 * MenuViewer.h
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUVIEWER_H_
#define INC_MENU_MENUVIEWER_H_

#include <MVC/View.h>

namespace Menu {

class MenuBox;
class MenuItem;
class MenuViewer: public MVC::View {
public:
								MenuViewer(MenuBox *menu);
	virtual 					~MenuViewer();

public:
	virtual void				onNotify();

private:
	void 						drawMenu(MenuBox* menu);
	void 						drawChild(const MenuItem* child, bool selected);
	void drawFooter();
	void drawTop();
};

} /* namespace Menu */

#endif /* INC_MENU_MENUVIEWER_H_ */
