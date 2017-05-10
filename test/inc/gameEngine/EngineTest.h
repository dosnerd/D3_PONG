/*
 * EngineTest.h
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#ifndef TEST_INC_GAMEENGINE_ENGINETEST_H_
#define TEST_INC_GAMEENGINE_ENGINETEST_H_

#include <Test.h>
#include <gameEngine/Coordinate.h>

namespace GameEngine {

class Engine;
class EngineTest: public Test {
public:
								EngineTest();
	virtual 					~EngineTest();

public:
	virtual bool				test();

private:
	Engine						*setupBasicField();
	void 						ZaxisOnly();
	GameEngine::Engine			*getGameField();
	void 						GameField(int cicles, GameEngine::Coordinate  speed);
};

} /* namespace GameEngine */

#endif /* TEST_INC_GAMEENGINE_ENGINETEST_H_ */
