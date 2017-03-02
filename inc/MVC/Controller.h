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
						Controller(Model *model);
		virtual         ~Controller();

	//overrides
	public:
		void            update();

	//getters
	public:
		virtual View    *getView();
		virtual Model   *getModel();

	public:
		void            setView(View *view);

	//member variables
	private:
		View            *view;
		Model           *model;
	};
}


#endif //TESTING_CONTROLLER_H
