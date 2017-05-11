/*
 * Model.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include <MVC/Model.h>
#include <MVC/Observer.h>

namespace MVC {

Model::Model() {
}

Model::~Model() {
}

/**
 * Go though list of observer to notify that data
 * has been changed
 */
void Model::notifyObservers() {
	uint16_t i;
	for (i=0; i < m_observers.length(); i++){
		m_observers[i]->notify();
	}
}

/**
 * Attach a observer that should be notified when an update
 * occurs
 */
void Model::attach(Observer *observer){
	m_observers.add(observer);
}

} /* namespace MVC */
