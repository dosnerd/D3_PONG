/*
 * Controller.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include <MVC/Controller.h>

namespace MVC {

Controller::Controller(Model *model)
	: Observer(model)
{

}

Controller::~Controller() {

}

} /* namespace MVC */
