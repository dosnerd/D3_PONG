//
// Created by Acer on 2-3-2017.
//

#include "MVC/View.h"

MVC::View::View() { }

MVC::View::~View() {

}

void MVC::View::update() {
	display();
}

MVC::Controller *MVC::View::getController() {
	return controller;
}

MVC::Model *MVC::View::getModel() {
	return model;
}
