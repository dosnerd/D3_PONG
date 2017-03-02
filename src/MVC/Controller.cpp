//
// Created by Acer on 2-3-2017.
//

#include "MVC/Controller.h"

MVC::Controller::Controller(Model *model)
		: model(model) { }

MVC::Controller::~Controller() { }

void MVC::Controller::update() { }

MVC::View *MVC::Controller::getView() {
	return view;
}

MVC::Model *MVC::Controller::getModel() {
	return model;
}

void MVC::Controller::setView(MVC::View *view) {
	Controller::view = view;
}
