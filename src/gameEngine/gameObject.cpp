/*
 * Object.cpp
 *
 *  Created on: 5 mei 2017
 *      Author: Acer
 */

#include <gameEngine/Coordinate.h>
#include <gameEngine/gameObject.h>

namespace GameEngine {

gameObject::gameObject(uint8_t width, uint8_t height)
	: m_location()
	, m_width(width), m_height(height)
{
}

gameObject::~gameObject() {

}

const bool gameObject::isCollided(gameObject* with, Coordinate at) {
	if (at.getZ() != m_location->getZ())
		return false;

	if (at.getX() <= m_location->getX() + m_width && at.getX() + with->m_width > m_location->getX()){
		if (at.getY() <= m_location->getY() + m_width && at.getY() + with->m_width > m_location->getY()){
			return true;
		}
	}
	return false;
}

const Coordinate gameObject::distanceTo(gameObject* object) {
	return *object->m_location - *m_location;
}

} /* namespace GameEngine */
