/*
 * SideWall.h
 *
 *  Created on: 8 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMEENGINE_SIDEWALL_H_
#define INC_GAMEENGINE_SIDEWALL_H_

#include <gameEngine/GameObject.h>

namespace GameEngine {

class SideWall: public GameObject {
public:
								SideWall(uint8_t width, uint8_t height);
	virtual 					~SideWall();

public:
	virtual const bool			isCollided(const GameObject* with, const Coordinate &at) const;
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_SIDEWALL_H_ */
