/*
 * Handball.h
 *
 *  Created on: 3 jun. 2017
 *      Author: Acer
 */

#ifndef INC_GAMECONTROLLERS_HANDBALL_H_
#define INC_GAMECONTROLLERS_HANDBALL_H_

#include <GameControllers/GameController.h>

namespace GameControllers {

class Handball : public GameController {
public:
								Handball(GameEngine::Ball *ball, PlayerController *player1, PlayerController *player2);
	virtual 					~Handball();

public:
	virtual void				setupField(GameEngine::Engine* engine);
	virtual void				onNotify();
	virtual void				play(bool scoreAsNumber = true);
	virtual void				winMatch(uint8_t player);

private:
	uint8_t						m_counter;
	static uint32_t				sTopscore;
	void 						updateScoreAndSpeed();
};

} /* namespace GameControllers */

#endif /* INC_GAMECONTROLLERS_HANDBALL_H_ */
