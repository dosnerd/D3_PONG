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
	, m_update(false)
{
	m_model->attach(this);
}

Observer::~Observer() {
}

/**
 * Called when model has changed. It indicate that something needs to be processed
 */
void Observer::notify(){ m_update = true; }

/**
 * Return boolean if the process method should be called. Is automatic reset update variable
 */
const bool Observer::needsProcess() {
	if (m_update){
		m_update = false;
		return true;
	}

	return false;
}

const Model *Observer::getModel() const {
	return m_model;
}
} /* namespace MVC */
