/*
 * MVCtest.h
 *
 *  Created on: 26 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_MVCTEST_H_
#define TEST_INC_MVCTEST_H_

#include <Test.h>
#include <Vector.h>
#include "MVC/ImplemController.h"
#include "MVC/ImplemModel.h"
#include "MVC/ImplemView.h"

class MVCtest: public Test {
public:
								MVCtest();
	virtual 					~MVCtest();

public:
	virtual bool 				test();

private:
	void						processObservers();
	void notifyController_changeToBig();
	void notifyController_changeToSmall();
	void notifyController_changeValid();
	void observersReset();
	void observerNotification();
	void notifyView();
	void allProcessed();

	Vector<MVC::Observer *>		m_observers;
	ImplemModel 				m_model;
	ImplemView	 				m_view;
	ImplemController 			m_controller;
};

#endif /* TEST_INC_MVCTEST_H_ */
