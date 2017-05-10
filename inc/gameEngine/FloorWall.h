/*
 * FloorWall.h
 *
 *  Created on: 10 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMEENGINE_FLOORWALL_H_
#define INC_GAMEENGINE_FLOORWALL_H_

#include <gameEngine/GameObject.h>

namespace GameEngine {

class FloorWall: public GameObject {
public:
								FloorWall(int32_t width, int32_t depth);
	virtual 					~FloorWall();

public:
	virtual const bool			isCollided(const GameObject* with, const Coordinate &at) const;
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_FLOORWALL_H_ */
