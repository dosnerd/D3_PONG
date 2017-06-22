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
	void 						animate();

private:
	uint8_t						m_lastSelected, m_animationDelay;
	uint16_t					m_animationColor;

	void 						drawMenu(MenuBox* menu);
	void 						drawChild(const MenuItem* child, bool selected);
	void 						drawFooter();
	void 						drawTop();
	void						animateColor(uint8_t shifter);
};

} /* namespace Menu */

#endif /* INC_MENU_MENUVIEWER_H_ */
