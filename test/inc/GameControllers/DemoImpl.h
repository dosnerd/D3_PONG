/*
 * DemoImpl.h
 *
 *  Created on: 22 mei 2017
 *      Author: Acer
 */

#ifndef TEST_INC_GAMECONTROLLERS_DEMOIMPL_H_
#define TEST_INC_GAMECONTROLLERS_DEMOIMPL_H_

#include <GameControllers/Demo.h>
#include <Vector.h>
#include <string.h>

namespace GameEngine {
	class Ball;
}

namespace GameControllers {

class DemoImpl : public Demo {
public:
								DemoImpl(GameEngine::Ball *ball);
	virtual 					~DemoImpl();

public:
	virtual void				winMatch(uint8_t player);
	Vector<uint8_t>& 			getStats();

private:
	Vector<uint8_t>				m_stats;
};

} /* namespace GameControllers */

#endif /* TEST_INC_GAMECONTROLLERS_DEMOIMPL_H_ */
