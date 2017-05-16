/*
 * Engine.cpp
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */
#define PRINT_DEBUG 0
#include <gameEngine/Engine.h>
#include <stdlib.h>

#if PRINT_DEBUG
#include <iostream>
#endif

#define NO_TRANSFORM 2*FIXED_POINT_MULTILIER

namespace GameEngine {

Engine::Engine() {

}

Engine::~Engine() {
	deleteAllObjects();
}

void Engine::moveBall() {
	Coordinate ballSpeed = m_ball.getSpeed();
	Vector<int32_t> transformList;
	int16_t i;

	getTransformFactors(ballSpeed, transformList);

	while(true){
		i = transformList.min();

		if (i == -1 || i == (int16_t)transformList.length() || transformList[i] == NO_TRANSFORM){
			m_ball.setPosition(m_ball.getPosition() + ballSpeed);
			ballSpeed = ballSpeed - ballSpeed;
			if (ballSpeed.getZ() == 0)
					return;
		} else {
			calcBounce(i, ballSpeed, transformList);
		}
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

Coordinate Engine::calcBounce(int16_t i, Coordinate& ballSpeed, Vector<int32_t>& transformList) {
	Coordinate intersection, intersection2, ballPos;
	GameObject* nearestObject = m_objectContainer[i];
	int32_t &transform = transformList[i];

	ballPos = getRelativeBall(nearestObject, ballPos);
	intersection = calcIntersection(m_ball.getPosition(), ballSpeed, transform);
	intersection2 = calcIntersection(ballPos, ballSpeed, transform);


	if (nearestObject->isCollided(&m_ball, intersection)) {
		ballSpeed.flip(nearestObject->getCompareAxis());
		m_ball.getSpeed().flip(nearestObject->getCompareAxis());
		if (existsSaveTransform(i, &transformList, &ballSpeed)) {
			transformList[i] = NO_TRANSFORM;
		} else {
			m_ball.setPosition(intersection);
			ballSpeed = (ballSpeed * FIXED_POINT_MULTILIER - ballSpeed * transformList[i]) / FIXED_POINT_MULTILIER;
			getTransformFactors(ballSpeed, transformList);
		}
	} else if (nearestObject->isCollided(&m_ball, intersection2)) {
		ballSpeed.flip(nearestObject->getCompareAxis());
		m_ball.getSpeed().flip(nearestObject->getCompareAxis());
		if (existsSaveTransform(i, &transformList, &ballSpeed)) {
			transformList[i] = NO_TRANSFORM;
		} else {
			m_ball.setPosition(intersection);
			ballSpeed = (ballSpeed * FIXED_POINT_MULTILIER - ballSpeed * transformList[i]) / FIXED_POINT_MULTILIER;
			getTransformFactors(ballSpeed, transformList);
		}
	} else {
		transformList[i] = NO_TRANSFORM;
	}

	return ballPos;
}

void Engine::getTransformFactors(Coordinate &speed, Vector<int32_t> &transformList) {
	int i, smallestFactor = -1;
	transformList.clear();

	for (i = 0; i < m_objectContainer.length(); ++i) {
		GameObject *object = m_objectContainer[i];
		int32_t transformFactor = getTransformFactor(object, speed);

		//check if object (like ball) will cross other object
		if (transformFactor > 0 && transformFactor <= 1 * FIXED_POINT_MULTILIER){
			if (transformFactor < smallestFactor || smallestFactor < 0) {
				smallestFactor = transformFactor;
			}
		} else {
			transformFactor = NO_TRANSFORM;
		}

		transformList.add(transformFactor);
	}
}

int32_t Engine::getTransformFactor(GameObject* object,
		Coordinate& ballSpeed)
{
	int32_t transformFactor = NO_TRANSFORM, transformFactorWithWitdh = NO_TRANSFORM;
	Coordinate::AXIS compareAxes = object->getCompareAxis();

	if (compareAxes != Coordinate::AXIS::NONE) {
		Coordinate distanceToMe = m_ball.distanceTo(object);
		Coordinate distanceToMe2 = object->getPosition() - (m_ball.getPosition() + Coordinate(m_ball.getWidth(), m_ball.getHeight(), 0));

		if (ballSpeed.get(compareAxes) != 0) {
			transformFactor = distanceToMe.get(compareAxes) * FIXED_POINT_MULTILIER / ballSpeed.get(compareAxes);
			transformFactorWithWitdh = distanceToMe2.get(compareAxes) * FIXED_POINT_MULTILIER / ballSpeed.get(compareAxes);

			if (transformFactorWithWitdh > 0 && transformFactorWithWitdh < transformFactor){
				transformFactor = transformFactorWithWitdh;
			}
		}
		else {
			transformFactor = NO_TRANSFORM;
		}
	}

	return transformFactor;
}


GameEngine::Coordinate Engine::calcIntersection(const Coordinate& ballPos, Coordinate& ballSpeed, int32_t& transform) {
	return (ballPos * FIXED_POINT_MULTILIER + ballSpeed * transform)
			/ FIXED_POINT_MULTILIER;
}

bool Engine::existsSaveTransform(int selected, Vector<int32_t> *transformList, Coordinate *ballSpeed) {
	int i;
	Coordinate intersection, intersection2, temp, temp2, ballPos;
	Coordinate::AXIS orientation = m_objectContainer[selected]->getCompareAxis();

	ballPos = getRelativeBall(m_objectContainer[selected], ballPos);
	intersection = calcIntersection(m_ball.getPosition(), *ballSpeed, (*transformList)[selected]);
	intersection2 = calcIntersection(ballPos, *ballSpeed, (*transformList)[selected]);

	for (i = 0; i < m_objectContainer.length(); ++i) {
		if (i != selected){
			ballPos = getRelativeBall(m_objectContainer[i], ballPos);
			orientation = m_objectContainer[i]->getCompareAxis();
			temp = calcIntersection(m_ball.getPosition(), *ballSpeed, (*transformList)[i]);
			temp2 = calcIntersection(ballPos, *ballSpeed, (*transformList)[i]);

			if (temp.get(orientation) == intersection.get(orientation)){
				return true;
			}
			if (temp2.get(orientation) == intersection2.get(orientation)){
				return true;
			}
		}
	}
	return transformList->min(selected+1) != selected && (*transformList)[transformList->min(selected+1)] == (*transformList)[selected];
}

Coordinate Engine::getRelativeBall(GameObject* nearestObject,
		Coordinate ballPos) {
	if (nearestObject->getCompareAxis() == Coordinate::X)
		ballPos = Coordinate(
				m_ball.getPosition().getX() + m_ball.getWidth(),
				m_ball.getPosition().getY(),
				m_ball.getPosition().getZ());
	else if (nearestObject->getCompareAxis() == Coordinate::Y)
		ballPos = Coordinate(
				m_ball.getPosition().getX(),
				m_ball.getPosition().getY() + m_ball.getHeight(),
				m_ball.getPosition().getZ());
	else
		ballPos = Coordinate(
				m_ball.getPosition().getX(),
				m_ball.getPosition().getY(),
				m_ball.getPosition().getZ());

	return ballPos;
}

void Engine::deleteAllObjects() {
	uint8_t i;
	for (i = 0; i < m_objectContainer.length(); ++i) {
		delete m_objectContainer[i];
	}
}

} /* namespace GameEngine */

