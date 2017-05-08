/*
 * Engine.h
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMEENGINE_ENGINE_H_
#define INC_GAMEENGINE_ENGINE_H_

#include <Vector.h>
#include <gameEngine/Ball.h>

class GameObject;
namespace GameEngine {

class Engine {
public:
								Engine();
	virtual 					~Engine();

public:
	virtual void				moveBall();
	Ball						*getBall();


public:
	virtual void				addObject(GameObject *object);
	virtual void				emtpyContainer();

private:
	Ball						m_ball;
	Vector<GameObject *>		m_objectContainer;

	void						getTransformFactors(Coordinate &speed, Vector<float> &transformList);
	float						getTransformFactor(GameObject* object,
										Coordinate& ballSpeed);

	void						deleteAllObjects();
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_ENGINE_H_ */
