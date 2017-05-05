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

class MVCtest: public Test {
public:
								MVCtest();
	virtual 					~MVCtest();

public:
	virtual bool 				test();

private:
	void						processObservers();

	Vector<MVC::Observer *>		m_observers;
};

#endif /* TEST_INC_MVCTEST_H_ */
