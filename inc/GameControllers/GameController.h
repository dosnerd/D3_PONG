/*
 * GameController.h
 *
 *  Created on: 11 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMECONTROLLERS_GAMECONTROLLER_H_
#define INC_GAMECONTROLLERS_GAMECONTROLLER_H_

#include <MVC/Controller.h>
#include <gameEngine/Coordinate.h>

#define GAMECONTROLLER_BAT1_PLAYER1		1
#define GAMECONTROLLER_BAT1_PLAYER2		2
#define GAMECONTROLLER_BAT2_PLAYER1		3
#define GAMECONTROLLER_BAT2_PLAYER2		4

class FPGA;

namespace GameEngine {
class Ball;
class Engine;
class GameObject;
}

namespace GameControllers {

class GameController : public MVC::Controller {
public:
									GameController(GameEngine::Ball *ball);
	virtual 						~GameController();

public:
	virtual void					play();
	virtual void					pause();
	virtual void					bind(FPGA *fpga);
	virtual void					setupField(GameEngine::Engine *engine);
	virtual void					onNotify();

protected:
	virtual void					winMatch(uint8_t player);
	virtual void					finishedGame();
	const FPGA						*getFpga() const;


protected:
	virtual GameEngine::Ball		*getBall();

protected:
	virtual GameEngine::GameObject	**getBats();

private:
	FPGA 							*m_fpga;
	GameEngine::GameObject			*m_bats[4];
	GameEngine::Coordinate			m_saveCoordinate;
};

} /* namespace GameControllers */

#endif /* INC_GAMECONTROLLERS_GAMECONTROLLER_H_ */
