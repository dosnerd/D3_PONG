/*
 * MVCtest.cpp
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#include <MVCtest.h>
#include <ImplemController.h>
#include <ImplemView.h>
#include <ImplemModel.h>

MVCtest::MVCtest()
	: Test("MVCtest")
{

}

MVCtest::~MVCtest() {

}

bool MVCtest::test() {
	ImplemModel m(0,0,0,0);
	ImplemController c(&m);
	MVC::Observer * t = &c;
	m_observers.add(t);

	processObservers();
	m.setData(1, 25);
	processObservers();

	return false;
}

void MVCtest::processObservers(){
	int i;
	for (i = 0; i < m_observers.length(); ++i) {
		if (m_observers[i]->needsProcess()){
			m_observers[i]->process();
			i = 0;
		}
	}
}
