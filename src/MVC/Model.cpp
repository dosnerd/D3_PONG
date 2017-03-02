//
// Created by Acer on 2-3-2017.
//

#include <algorithm>
#include <MVC/Observer.h>
#include "MVC/Model.h"

MVC::Model::Model() { }

MVC::Model::~Model() {

}

void MVC::Model::attach(MVC::Observer *observer) {
	observers.push_back(observer);
}

void MVC::Model::detach(MVC::Observer *observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void MVC::Model::notify() {
	//foreach observer, update
	for (unsigned int i = 0; i < observers.size(); ++i) {
		observers[i]->update();
	}
}
