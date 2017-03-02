//
// Created by Acer on 2-3-2017.
//

#ifndef TESTING_VIEW_H
#define TESTING_VIEW_H

#include "Observer.h"

namespace MVC {
	class Controller;
	class Model;

	class View : public Observer {
	//constructors
	public:
							View();
		virtual             ~View();

	//members functions
	public:
		virtual void        display() = 0;

	//overrides
	public:
		void                update();

	//getters
	public:
		virtual Controller  *getController();
		virtual Model       *getModel();

		//member veriables
	private:
		Controller          *controller;
		Model               *model;
	};
}


#endif //TESTING_VIEW_H
