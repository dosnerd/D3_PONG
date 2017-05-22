/*
 * MVCtest.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include <MVCtest.h>

MVCtest::MVCtest()
	: Test("MVCtest")
	, m_model(0, 0, 0, 0)
	, m_view(&m_model)
	, m_controller(&m_model)
{
	MVC::Observer *controller = &m_controller;
	MVC::Observer *view = &m_view;

	m_observers.add(controller);
	m_observers.add(view);
}

MVCtest::~MVCtest() {

}

void MVCtest::notifyController_changeToBig() {
	m_model.setData(1, 25);
	failIfDifferent(m_model.getData(1), 25, "Not 25: Invalid change");
	processObservers();
	failIfDifferent(m_model.getData(1), 10, "Not 10: Observer not notified");
}

void MVCtest::notifyController_changeToSmall() {
	m_model.setData(1, -10);
	failIfDifferent(m_model.getData(1), -10, "Not -10: Invalid change");
	processObservers();
	failIfDifferent(m_model.getData(1), 0, "Not 10: Observer not notified");
}

void MVCtest::notifyController_changeValid() {
	m_model.setData(1, 5);
	failIfDifferent(m_model.getData(1), 5, "Not 5: Invalid change");
	processObservers();
	failIfDifferent(m_model.getData(1), 5, "Not 5: Invalid change");
}

void MVCtest::observersReset() {
	int i;

	m_model.setData(0, m_model.getData(0));
	processObservers(false);

	for (i = 0; i < m_observers.length(); ++i) {
		failIfDifferent(m_observers[i]->isNotified(), false,
					"Observer notified when no changes");
	}
}

void MVCtest::observerNotification() {
	m_model.setData(0, m_model.getData(0));
	failIfDifferent(m_controller.isNotified(), true, "No notification");
}

void MVCtest::notifyView() {
	m_model.setData(2, 5);
	processObservers();
	failIfDifferent(m_view.getValidData(2), 5, "View not notified");
}

void MVCtest::allProcessed() {
	m_model.setData(2, 20);
	processObservers();
	failIfDifferent(m_view.getValidData(2), 10, "Not all observer processed 20");
	m_model.setData(2, -20);
	processObservers();
	failIfDifferent(m_view.getValidData(2), 0, "Not all observer processed -20");
}

bool MVCtest::test() {
	observerNotification();
	observersReset();
	notifyController_changeToBig();
	notifyController_changeToSmall();
	notifyController_changeValid();

	notifyView();
	allProcessed();
	return true;
}

void MVCtest::processObservers(bool rerunOnNotify){
	int i;

	if (rerunOnNotify)
		MVC::Observer::handleNotifications();
	else
		for (i = 0; i < m_observers.length(); ++i) {
			if (m_observers[i]->isNotified()){
				m_observers[i]->onNotify();
			}
		}
}
