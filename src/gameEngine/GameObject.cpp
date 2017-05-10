/*
 * Object.cpp
 *
 *  Created on: 5 mei 2017
 *      Author: Acer
 */

#include <gameEngine/Coordinate.h>
#include <gameEngine/GameObject.h>

namespace GameEngine {

GameObject::GameObject(Coordinate::AXIS compareAxis, int32_t width, int32_t height)
	: m_position()
	, m_compareAxis(compareAxis)
	, m_width(width), m_height(height)
{
}

GameObject::~GameObject() {

}

const bool GameObject::isCollided(const GameObject* with, const Coordinate &at) const {
	if (at.getZ() != m_position.getZ())
		return false;

	if (at.getX() <= m_position.getX() + m_width && at.getX() + with->m_width > m_position.getX()){
		if (at.getY() <= m_position.getY() + m_height && at.getY() + with->m_height > m_position.getY()){
			return true;
		}
	}
	return false;
}

Coordinate GameObject::distanceTo(const GameObject* object) const {
	return object->m_position - m_position;
}

const Coordinate::AXIS GameObject::getCompareAxis() const {
	return m_compareAxis;
}

const Coordinate& GameEngine::GameObject::getPosition() const {
	return m_position;
}

void GameEngine::GameObject::setPosition(const Coordinate& position) {
	m_position = position;
}

int32_t GameEngine::GameObject::getHeight() const {
	return m_height;
}

int32_t GameEngine::GameObject::getWidth() const {
	return m_width;
}

} /* namespace GameEngine */
