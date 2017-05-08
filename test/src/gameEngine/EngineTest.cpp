/*
 * EngineTest.cpp
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#include <gameEngine/EngineTest.h>
#include <gameEngine/Engine.h>
#include <gameEngine/SideWall.h>

#include <iostream>

namespace GameEngine {

EngineTest::EngineTest()
	: Test("Game Engine Test")
{
}

EngineTest::~EngineTest() {
}

Engine *EngineTest::setupBasicField() {
	Engine* engine = new Engine();
	GameObject* wallTop = new GameObject(Coordinate::Z, 100, 100);
	GameObject* wallBottom = new GameObject(Coordinate::Z, 100, 100);
	GameObject* wallLeft = new SideWall(100, 100);
	GameObject* wallRight = new SideWall(100, 100);

	wallBottom->setPosition(Coordinate(0, 0, 100));
	wallRight->setPosition(Coordinate(100, 0, 0));
	engine->getBall()->setPosition(Coordinate(10, 10, 0));
	engine->getBall()->setSpeed(Coordinate(0, 0, 1));

	engine->addObject(wallTop);
	engine->addObject(wallBottom);
	engine->addObject(wallLeft);
	engine->addObject(wallRight);

	return engine;
}

void EngineTest::ZaxisOnly() {
	Engine* engine = setupBasicField();
	int i;
	for (i = 0; i < 110; ++i) {
		engine->moveBall();
	}

	if (engine->getBall()->getPosition().getZ() != 90)
		fail("Z only: z-position != 90");
	if (engine->getBall()->getSpeed().getZ() != -1)
		fail("Z only: z-speed != 90");

	delete engine;
}

bool EngineTest::test() {
	ZaxisOnly();

	Engine* engine = setupBasicField();
	int i;

	engine->getBall()->setPosition(Coordinate(10, 10, 10));
	engine->getBall()->setSpeed(Coordinate(3, 0, 5));
	for (i = 0; i < 110; ++i) {
		engine->moveBall();
		std::cout << (int) (engine->getBall()->getPosition().getX()) << ":";
		std::cout << (int) (engine->getBall()->getPosition().getY()) << ":";
		std::cout << (int) (engine->getBall()->getPosition().getZ());
		std::cout << "   ";
		std::cout << (int) (engine->getBall()->getSpeed().getX()) << ":";
		std::cout << (int) (engine->getBall()->getSpeed().getY()) << ":";
		std::cout << (int) (engine->getBall()->getSpeed().getZ());
		std::cout << std::endl;
	}

	delete engine;

	return true;
}

} /* namespace GameEngine */
