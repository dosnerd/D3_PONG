/*
 * ObjectTest.h
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#ifndef TEST_INC_GAMEENGINE_GAMEOBJECTTEST_H_
#define TEST_INC_GAMEENGINE_GAMEOBJECTTEST_H_

#include <Test.h>

namespace GameEngine {

class GameObjectTest: public Test {
public:
								GameObjectTest();
	virtual 					~GameObjectTest();

public:
	virtual bool				test();
};

} /* namespace GameEngine */

#endif /* TEST_INC_GAMEENGINE_GAMEOBJECTTEST_H_ */
