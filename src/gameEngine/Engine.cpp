/*
 * Engine.cpp
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#include <gameEngine/Engine.h>
#include <stdlib.h>

#include <iostream>

#define NO_TRANSFORM 2

namespace GameEngine {

Engine::Engine() {

}

Engine::~Engine() {
	deleteAllObjects();
}

void Engine::moveBall() {
	Coordinate intersection, ballSpeed = m_ball.getSpeed();
	Vector<float> transformList;
	GameObject *nearestObject;
	uint8_t i;
	getTransformFactors(ballSpeed, transformList);

	while(true){
		i = transformList.min();
//		std::cout << "(" << (int)i << ", "  << (int)transformList[i] << ")";

		if (i == -1 || i == transformList.length() || transformList[i] == NO_TRANSFORM){
			m_ball.setPosition(m_ball.getPosition() + ballSpeed);
			ballSpeed = ballSpeed - ballSpeed;
			if (ballSpeed.getZ() == 0)
					return;
		} else {
			intersection = m_ball.getPosition() + ballSpeed * transformList[i];
			nearestObject = m_objectContainer[i];

//			std::cout << "[";
//
//
//			Coordinate temp = ballSpeed * transformList[i];
//
//			std::cout << (int)intersection.getX() << ":";
//			std::cout << (int)intersection.getY() << ":";
//			std::cout << (int)intersection.getZ();
//
//			std::cout << "]";

			if (nearestObject->isCollided(&m_ball, intersection)){
//				std::cout << "Kabom" << std::endl;

				m_ball.setPosition(intersection);
				ballSpeed = ballSpeed - ballSpeed * transformList[i];

				ballSpeed.flip(nearestObject->getCompareAxis());
				m_ball.getSpeed().flip(nearestObject->getCompareAxis());

				if (transformList[transformList.min(i+1)] == transformList[i]){
					transformList[i] = NO_TRANSFORM;
				} else {
					getTransformFactors(ballSpeed, transformList);
				}
			} else {
				std::cout << "No collision" << std::endl;
				transformList[i] = NO_TRANSFORM;
			}
		}
	}
//	std::cout << "  END  ";
}

float Engine::getTransformFactor(GameObject* object,
		Coordinate& ballSpeed)
{
	float transformFactor = NO_TRANSFORM;
	Coordinate::AXIS compareAxes = object->getCompareAxis();

	if (compareAxes != Coordinate::AXIS::NONE) {
		Coordinate distanceToMe = m_ball.distanceTo(object);
		transformFactor = ((float) (distanceToMe.get(compareAxes)))
				/ ballSpeed.get(compareAxes);
	}

	return transformFactor;
}

void Engine::getTransformFactors(Coordinate &speed, Vector<float> &transformList) {
	int i, nearestObject, smallestFactor = -1;
	transformList.clear();

	for (i = 0; i < m_objectContainer.length(); ++i) {
		GameObject *object = m_objectContainer[i];
		float transformFactor = getTransformFactor(object, speed);

//		std::cout << transformFactor << "**" ;

		//check if object (like ball) will cross other object
		if (transformFactor > 0 && transformFactor <= 1){
			if (transformFactor < smallestFactor || smallestFactor < 0) {
				nearestObject = i;
				smallestFactor = transformFactor;
			}
		} else {
			transformFactor = NO_TRANSFORM;
		}

		transformList.add(transformFactor);
	}
}

void Engine::addObject(GameObject* object) {
	if (object != nullptr){
		m_objectContainer.add(object);
	}
}

void Engine::emtpyContainer() {
	deleteAllObjects();
}

Ball *Engine::getBall() {
	return &m_ball;
}

void Engine::deleteAllObjects() {
	uint8_t i;
	for (i = 0; i < m_objectContainer.length(); ++i) {
		delete m_objectContainer[i];
	}
}

} /* namespace GameEngine */

