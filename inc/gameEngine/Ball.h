/*
 * Ball.h
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMEENGINE_BALL_H_
#define INC_GAMEENGINE_BALL_H_

#include <gameEngine/GameObject.h>
#include <GameEngine/Coordinate.h>
#include <MVC/Model.h>

namespace GameEngine {

class Ball: public GameObject, public MVC::Model {
public:
								Ball();
	virtual 					~Ball();

public:
	virtual const bool			isCollided(GameObject* with, Coordinate at);

public:
	Coordinate& 				getSpeed();
	void 						setSpeed(const Coordinate& speed);
	void 						setPosition(const Coordinate& position);

private:
	Coordinate					m_speed;
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_BALL_H_ */
