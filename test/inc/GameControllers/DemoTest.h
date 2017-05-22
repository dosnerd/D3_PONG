/*
 * DemoTest.h
 *
 *  Created on: 22 mei 2017
 *      Author: Acer
 */

#ifndef TEST_INC_GAMECONTROLLERS_DEMOTEST_H_
#define TEST_INC_GAMECONTROLLERS_DEMOTEST_H_

#include <Test.h>

namespace GameControllers {

class DemoTest: public Test {
public:
								DemoTest();
	virtual 					~DemoTest();

public:
	virtual bool				test();

private:
	void dummyTest(uint32_t ticks);
};

} /* namespace GameControllers */

#endif /* TEST_INC_GAMECONTROLLERS_DEMOTEST_H_ */
