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
	virtual GameEngine::GameObject	*getBat(uint8_t player);

private:
	FPGA 							*m_fpga;
	GameEngine::GameObject			*m_bat1, *m_bat2;
	GameEngine::Coordinate			m_saveCoordinate;
};

} /* namespace GameControllers */

#endif /* INC_GAMECONTROLLERS_GAMECONTROLLER_H_ */
