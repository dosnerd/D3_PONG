//
// Created by Acer on 2-3-2017.
//

#ifndef TESTING_CONTROLLER_H
#define TESTING_CONTROLLER_H


#include <MVC/Observer.h>

namespace MVC {
	class Model;
	class View;

	class Controller: public Observer {
	//constructors
	public:
		Controller();
		virtual ~Controller();

	//overrides
	public:
		void update() override;

	//getters
	public:
		virtual View    *getView();
		virtual Model   *getModel();

	//member variables
	private:
		View            *view;
		Model           *model;
	};
}


#endif //TESTING_CONTROLLER_H
