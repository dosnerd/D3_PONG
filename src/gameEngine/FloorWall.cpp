/*
 * FloorWall.cpp
 *
 *  Created on: 10 mei 2017
 *      Author: Acer
 */

#include <gameEngine/FloorWall.h>

namespace GameEngine {

FloorWall::FloorWall(int32_t width, int32_t depth)
	: GameObject(Coordinate::Y, width, depth)
{

}

FloorWall::~FloorWall() {
}


const bool FloorWall::isCollided(const GameObject* with, const Coordinate &at) const {
	if (at.getY() != getPosition().getY())
		return false;

	if (at.getX() <= getPosition().getX() + getWidth() && at.getX() + with->getWidth() > getPosition().getX()){
		if (at.getZ() <= getPosition().getZ() + getHeight() && at.getZ() + with->getHeight() > getPosition().getZ()){
			return true;
		}
	}
	return false;
}

} /* namespace GameEngine */
