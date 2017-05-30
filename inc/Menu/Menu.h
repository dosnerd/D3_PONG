/*
 * Menu.h
 *
 *  Created on: 29 mei 2017
 *      Author: Acer
 */

#ifndef INC_MENU_MENU_H_
#define INC_MENU_MENU_H_

namespace Menu {

class Menu {
public:
								Menu() { };
	virtual 					~Menu() { };

public:
	virtual void				print() = 0;
	virtual void				select() = 0;
	virtual void				up() { };
	virtual void				down() { };
	virtual void				left() { };
	virtual void				right() { };
};

} /* namespace Menu */

#endif /* INC_MENU_MENU_H_ */
