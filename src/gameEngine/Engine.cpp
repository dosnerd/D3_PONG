/*
 * Engine.cpp
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#include <gameEngine/Engine.h>
#include <stdlib.h>

//#include <iostream>

#define NO_TRANSFORM 2*FIXED_POINT_MULTILIER

namespace GameEngine {

Engine::Engine() {

}

Engine::~Engine() {
	deleteAllObjects();
}

void Engine::moveBall() {
	Coordinate intersection, intersection2, ballPos, ballSpeed = m_ball.getSpeed();
	Vector<int32_t> transformList;
	GameObject *nearestObject;
	int16_t i;

	getTransformFactors(ballSpeed, transformList);

	while(true){
		i = transformList.min();
//		std::cout << "(" << (int)i << ", "  << (int)transformList[i] << ")";

		if (i == -1 || i == (int16_t)transformList.length() || transformList[i] == NO_TRANSFORM){
			m_ball.setPosition(m_ball.getPosition() + ballSpeed);
			ballSpeed = ballSpeed - ballSpeed;
			if (ballSpeed.getZ() == 0)
					return;
		} else {
			nearestObject = m_objectContainer[i];
			if (nearestObject->getCompareAxis() == Coordinate::X)
				ballPos = Coordinate(
						m_ball.getPosition().getX() + m_ball.getWidth(),
						m_ball.getPosition().getY(),
						m_ball.getPosition().getZ()
						);
			else if (nearestObject->getCompareAxis() == Coordinate::Y)
				ballPos = Coordinate(
						m_ball.getPosition().getX(),
						m_ball.getPosition().getY() + m_ball.getHeight(),
						m_ball.getPosition().getZ()
						);
			else
				ballPos = Coordinate(
						m_ball.getPosition().getX(),
						m_ball.getPosition().getY(),
						m_ball.getPosition().getZ()
						);

			intersection =
					(m_ball.getPosition() * FIXED_POINT_MULTILIER +
					ballSpeed * transformList[i]) / FIXED_POINT_MULTILIER;
			intersection2 =
					(ballPos * FIXED_POINT_MULTILIER +
					ballSpeed * transformList[i]) / FIXED_POINT_MULTILIER;


//			std::cout << std::endl << "[";
////
////
//////			Coordinate temp = ballSpeed * transformList[i];
//			Coordinate temp = intersection;
//////			Coordinate temp = m_ball.getPosition();
////
//			std::cout << (int)temp.getX() << ":";
//			std::cout << (int)temp.getY() << ":";
//			std::cout << (int)temp.getZ();
//
//			std::cout << ",";
//
//			temp = intersection2;
//
//			std::cout << (int)temp.getX() << ":";
//			std::cout << (int)temp.getY() << ":";
//			std::cout << (int)temp.getZ();
//
//			std::cout << ",";
//
//////			temp = m_ball.getPosition() * FIXED_POINT_MULTILIER;
//			temp = nearestObject->getPosition();
////
//			std::cout << (int)temp.getX() << ":";
//			std::cout << (int)temp.getY() << ":";
//			std::cout << (int)temp.getZ();
//
//			std::cout << "]" << std::endl;

			if (nearestObject->isCollided(&m_ball, intersection)){
//				std::cout << "Kabom" << std::endl;
				m_ball.setPosition(intersection);
				ballSpeed = (ballSpeed * FIXED_POINT_MULTILIER - ballSpeed * transformList[i]) / FIXED_POINT_MULTILIER;

				ballSpeed.flip(nearestObject->getCompareAxis());
				m_ball.getSpeed().flip(nearestObject->getCompareAxis());

				if (transformList[transformList.min(i+1)] == transformList[i]){
					transformList[i] = NO_TRANSFORM;
				} else {
					getTransformFactors(ballSpeed, transformList);
				}
			}
			else if (nearestObject->isCollided(&m_ball, intersection2)){
//				std::cout << "Poef" << std::endl;
				m_ball.setPosition(intersection);
				ballSpeed = (ballSpeed * FIXED_POINT_MULTILIER - ballSpeed * transformList[i]) / FIXED_POINT_MULTILIER;

				ballSpeed.flip(nearestObject->getCompareAxis());
				m_ball.getSpeed().flip(nearestObject->getCompareAxis());

				if (transformList[transformList.min(i+1)] == transformList[i]){
					transformList[i] = NO_TRANSFORM;
				} else {
					getTransformFactors(ballSpeed, transformList);
				}
			}
			else {
//				std::cout << "No collision" << std::endl;
				transformList[i] = NO_TRANSFORM;
			}
		}
	}
//	std::cout << "  END  ";
}

int32_t Engine::getTransformFactor(GameObject* object,
		Coordinate& ballSpeed)
{
	int32_t transformFactor = NO_TRANSFORM, transformFactorWithWitdh = NO_TRANSFORM;
	Coordinate::AXIS compareAxes = object->getCompareAxis();

	if (compareAxes != Coordinate::AXIS::NONE) {
		Coordinate distanceToMe = m_ball.distanceTo(object);
		Coordinate distanceToMe2 = object->getPosition() - (m_ball.getPosition() + Coordinate(m_ball.getWidth(), m_ball.getHeight(), 0));

//		std::cout << "[";
//
//					std::cout << distanceToMe2.getX() << ":";
//					std::cout << distanceToMe2.getY() << ":";
//					std::cout << distanceToMe2.getZ();
//					std::cout << ",";
//					std::cout << distanceToMe.getX() << ":";
//					std::cout << distanceToMe.getY() << ":";
//					std::cout << distanceToMe.getZ();
//		std::cout << "]";

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

void Engine::getTransformFactors(Coordinate &speed, Vector<int32_t> &transformList) {
	int i, smallestFactor = -1;
	transformList.clear();

	for (i = 0; i < m_objectContainer.length(); ++i) {
		GameObject *object = m_objectContainer[i];
		int32_t transformFactor = getTransformFactor(object, speed);

//		std::cout << transformFactor << "**" ;

		//check if object (like ball) will cross other object
		if (transformFactor > 0 && transformFactor <= 1 * FIXED_POINT_MULTILIER){
			if (transformFactor < smallestFactor || smallestFactor < 0) {
				smallestFactor = transformFactor;
			}
		} else {
//			std::cout << "." << transformFactor;
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

