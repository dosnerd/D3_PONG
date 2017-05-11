/*
 * View.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include <MVC/View.h>

namespace MVC {

View::View(Model *model)
	: Observer(model)
{
}

View::~View() {

}

} /* namespace MVC */
