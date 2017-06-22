/*
 * Coordinatetest.h
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#ifndef TEST_INC_GAMEENGINE_COORDINATETEST_H_
#define TEST_INC_GAMEENGINE_COORDINATETEST_H_

#include <Test.h>

namespace GameEngine {

class CoordinateTest : public Test {
public:
								CoordinateTest();
	virtual 					~CoordinateTest();

public:
	virtual bool				test();

};

} /* namespace GameEngine */

#endif /* TEST_INC_GAMEENGINE_COORDINATETEST_H_ */
