/*
 * SideWall.cpp
 *
 *  Created on: 8 mei 2017
 *      Author: Acer
 */

#include <gameEngine/SideWall.h>

namespace GameEngine {

SideWall::SideWall(int32_t width, int32_t height)
	: GameObject(Coordinate::X, width, height)
{

}

SideWall::~SideWall() {

}

const bool SideWall::isCollided(const GameObject* with, const Coordinate& at) const {
	if (at.getX() != getPosition().getX())
		return false;

	if (at.getZ() <= getPosition().getZ() + getWidth() && at.getZ() + with->getWidth() > getPosition().getZ()) {
		if (at.getY() <= getPosition().getY() + getHeight() && at.getY() + with->getHeight() > getPosition().getY()) {
			return true;
		}
	}
	return false;
}

const uint8_t GameEngine::SideWall::getEffectSides(const GameObject* with, const Coordinate& at) const {
	(void)with;
	(void)at;
	return 0;
}

} /* namespace GameEngine */
