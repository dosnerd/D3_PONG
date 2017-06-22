/*
 * Controller.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef INC_MVC_CONTROLLER_H_
#define INC_MVC_CONTROLLER_H_

#include <MVC/Observer.h>

namespace MVC {

class Controller: public Observer {
public:
								Controller(Model *model);
	virtual 					~Controller();
};

} /* namespace MVC */

#endif /* INC_MVC_CONTROLLER_H_ */
