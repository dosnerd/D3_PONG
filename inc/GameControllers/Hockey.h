/*
 * Hockey.h
 *
 *  Created on: 4 jun. 2017
 *      Author: Acer
 */

#ifndef INC_GAMECONTROLLERS_HOCKEY_H_
#define INC_GAMECONTROLLERS_HOCKEY_H_

#include <GameControllers/GameController.h>

namespace GameControllers {

class Hockey: public GameController {
public:
								Hockey(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2);
	virtual 					~Hockey();

public:
	virtual void				setupField(GameEngine::Engine *engine);
	virtual void				onNotify();
};

} /* namespace GameControllers */

#endif /* INC_GAMECONTROLLERS_HOCKEY_H_ */
