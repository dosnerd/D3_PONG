/*
 * Demo.h
 *
 *  Created on: 16 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMECONTROLLERS_DEMO_H_
#define INC_GAMECONTROLLERS_DEMO_H_

#include <GameControllers/GameController.h>

namespace GameEngine{
	class ball;
}

namespace GameControllers {

class Demo: public GameController {
public:
									Demo(GameEngine::Ball *ball);
	virtual 						~Demo();

public:
	virtual void					onNotify();

private:
	uint8_t							m_counter;

	void							moveBat();
	void 							updateLimits();
	const GameEngine::Coordinate	*getBallPosition(const GameEngine::Coordinate& ballSpeed, uint8_t player);
	GameEngine::Coordinate 			calcBatNewPosition(const GameEngine::Coordinate* batPosition, const GameEngine::Coordinate& batSpeed);
	GameEngine::Coordinate 			calcBatSpeed(uint8_t player, const GameEngine::Coordinate* batPosition);
};

} /* namespace GameControllers */

#endif /* INC_GAMECONTROLLERS_DEMO_H_ */
