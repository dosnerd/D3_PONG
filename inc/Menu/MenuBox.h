/*
 * MenuBox.h
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENUBOX_H_
#define INC_MENU_MENUBOX_H_

#include <MVC/Model.h>

namespace Menu {

class MenuItem;
class MenuBox: public MVC::Model {
public:
								MenuBox();
	virtual 					~MenuBox();

public:
	virtual void				show(MenuItem *item);
	virtual void				hide();
	virtual void				select();

public:
	virtual void				up();
	virtual void				down();
	virtual void				goTo(uint8_t child);

public:
	virtual bool				isShowing();
	virtual const uint8_t		&getSelected() const;
	virtual MenuItem			*getCurrentMenu();

public:
	static MenuBox				*getInstance();

private:
	static MenuBox				sInstance;
	uint8_t						m_iCurrent;
	MenuItem					*m_current;

};

} /* namespace Menu */

#endif /* INC_MENU_MENUBOX_H_ */
