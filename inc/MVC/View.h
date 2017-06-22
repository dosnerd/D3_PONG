/*
 * View.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef INC_MVC_VIEW_H_
#define INC_MVC_VIEW_H_

#include <MVC/Observer.h>

namespace MVC {

class Controller;
class View: public Observer {
public:
								View(Model *model);
	virtual 					~View();
};

} /* namespace MVC */

#endif /* INC_MVC_VIEW_H_ */
