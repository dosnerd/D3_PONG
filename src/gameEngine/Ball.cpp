/*
 * Ball.cpp
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#include <gameEngine/Ball.h>

namespace GameEngine {

Ball::Ball()
	: GameObject(Coordinate::Z, 10, 10)
	, m_speed(3, 3, 3)
{

}

Ball::~Ball() {
}

const bool Ball::isCollided(GameObject* with, Coordinate at) {
	//TODO: create specialized collide detect
	return GameObject::isCollided(with, at);
}

Coordinate& Ball::getSpeed() {
	return m_speed;
}

void Ball::setSpeed(const Coordinate& speed) {
	m_speed = speed;
}

} /* namespace GameEngine */

