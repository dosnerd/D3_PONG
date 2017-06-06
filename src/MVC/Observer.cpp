/*
 * Observer.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include <MVC/Observer.h>
#include <MVC/Model.h>

namespace MVC {

Vector<Observer *> *Observer::sObserverContainer = nullptr;

void Observer::checkContainerExists() {
	static Vector<Observer*> container;
	if (sObserverContainer == nullptr)
		sObserverContainer = &container;
}

Observer::Observer(Model *model)
	: m_model(model)
	, m_notifyFlag(false)
{
	checkContainerExists();

	Observer *t = this;
	sObserverContainer->add(t);
	m_model->attach(this);
}

Observer::~Observer() {
	int i;
	for (i = 0; i < sObserverContainer->length(); ++i) {

		if ((*sObserverContainer)[i] == this){
			sObserverContainer->remove(i);
			return;
		}
	}
}

/**
 * Called when model has changed. It indicate that something needs to be processed
 */
void Observer::notify(){ m_notifyFlag = true; }

/**
 * Return boolean if the process method should be called. Is automatic reset update variable
 */
const bool Observer::isNotified() const {
	return m_notifyFlag;
}

const void Observer::resetNotifyFlag() {
	m_notifyFlag = false;
}

void Observer::handleNotifications() {
	int i;
	for (i = 0; i < sObserverContainer->length(); ++i) {
		if ((*sObserverContainer)[i]->isNotified()){
			(*sObserverContainer)[i]->onNotify();
			i = -1;
		}
	}
}

void Observer::emptyContainer() {
	sObserverContainer->clear();
}

const Model *Observer::getModel() const {
	return m_model;
}


} /* namespace MVC */
