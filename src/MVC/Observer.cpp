/*
 * Observer.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include <MVC/Observer.h>
#include <MVC/Model.h>

namespace MVC {

Observer::Observer(Model *model)
	: m_model(model)
	, m_notifyFlag(false)
{
	m_model->attach(this);
}

Observer::~Observer() {
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

const Model *Observer::getModel() const {
	return m_model;
}

} /* namespace MVC */
