/*
 * Tennis.h
 *
 *  Created on: 15 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMECONTROLLERS_TENNIS_H_
#define INC_GAMECONTROLLERS_TENNIS_H_

#include <GameControllers/GameController.h>

namespace GameControllers {

class Tennis: public GameController {
public:
								Tennis(GameEngine::Ball *ball);
	virtual 					~Tennis();

public:
	virtual void				onNotify();
};

} /* namespace GameControllers */

#endif /* INC_GAMECONTROLLERS_TENNIS_H_ */
