//
// Created by Acer on 2-3-2017.
//

#include "MVC/View.h"

MVC::View::View(Model *model, Controller *controller)
		: model(model), controller(controller) {
}

MVC::View::~View() {

}

void MVC::View::update() {
	//standard view update will refresh screen
	display();
}

MVC::Controller *MVC::View::getController() {
	return controller;
}

MVC::Model *MVC::View::getModel() {
	return model;
}
