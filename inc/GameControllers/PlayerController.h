/*
 * PlayerController.h
 *
 *  Created on: 30 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMECONTROLLERS_PLAYERCONTROLLER_H_
#define INC_GAMECONTROLLERS_PLAYERCONTROLLER_H_

#include <MVC/Controller.h>
#include <gameEngine/Coordinate.h>

class Stream;

namespace GameControllers {

class PlayerController: public MVC::Controller {
public:
								PlayerController(Stream *stream);
	virtual 					~PlayerController();

public:
	virtual void				onNotify();

public:
	uint16_t 					getScore() const;
	void 						setScore(uint16_t score);


private:
	uint16_t					m_score;
	uint16_t 					m_cmd;
	Stream 						*m_stream;
	GameEngine::Coordinate		m_position;

	void 						runCommand();
	void getPosition();
};

} /* namespace GameControllers */

#endif /* INC_GAMECONTROLLERS_PLAYERCONTROLLER_H_ */
