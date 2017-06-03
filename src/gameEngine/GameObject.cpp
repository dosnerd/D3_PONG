/*
 * Object.cpp
 *
 *  Created on: 5 mei 2017
 *      Author: Acer
 */

#include <gameEngine/GameObject.h>
#include <gameEngine/Coordinate.h>
#include <config_file.h>

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

const uint8_t GameObject::getEffectSides(const GameObject* with, const Coordinate &at) const {
	uint8_t bouncing_side = 0;
	Coordinate otherSideAt(at), otherSideSelf(m_position);
	otherSideAt.setX(otherSideAt.getX() + with->getWidth());
	otherSideAt.setY(otherSideAt.getY() + with->getHeight());
	otherSideSelf.setX(otherSideSelf.getX() + getWidth());
	otherSideSelf.setY(otherSideSelf.getY() + getHeight());


	if (at.getX() >= m_position.getX() && at.getX() - SPACE_BOUNCING_EFFECT <= m_position.getX()){
		bouncing_side = GAMEOBJECT_BOUNCE_EFFECT_TOP;
	} else if (otherSideAt.getX() <= otherSideSelf.getX() && otherSideAt.getX() + SPACE_BOUNCING_EFFECT >= otherSideSelf.getX()){
		bouncing_side = GAMEOBJECT_BOUNCE_EFFECT_BOTTOM;
	}
	if (at.getY() >= m_position.getY() && at.getY() - SPACE_BOUNCING_EFFECT <= m_position.getY()){
		bouncing_side |= GAMEOBJECT_BOUNCE_EFFECT_LEFT;
	} else if (otherSideAt.getY() <= otherSideSelf.getY() && otherSideAt.getY() + SPACE_BOUNCING_EFFECT >= otherSideSelf.getY()){
		bouncing_side |= GAMEOBJECT_BOUNCE_EFFECT_RIGHT;
	}

	return bouncing_side;
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
