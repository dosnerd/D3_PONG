/*
 * EngineTest.cpp
 *
 *  Created on: 7 mei 2017
 *      Author: Acer
 */

#include <gameEngine/EngineTest.h>
#include <gameEngine/Engine.h>
#include <gameEngine/SideWall.h>
#include <gameEngine/FloorWall.h>

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

	if (engine->getBall()->getPosition().getZ() != 90){
		delete engine;
		fail("Z only: z-position != 90");
	}
	if (engine->getBall()->getSpeed().getZ() != -1){
		delete engine;
		fail("Z only: z-speed != 90");
	}

	delete engine;
}

GameEngine::Engine* EngineTest::getGameField() {
	GameEngine::Engine* engine = new GameEngine::Engine();
	GameEngine::GameObject* wallFront = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
	GameEngine::GameObject* wallBack = new GameEngine::GameObject(GameEngine::Coordinate::Z, 640, 480);
	GameEngine::GameObject* wallLeft = new GameEngine::SideWall(100, 480);
	GameEngine::GameObject* wallRight = new GameEngine::SideWall(100, 480);
	GameEngine::GameObject* wallTop = new GameEngine::FloorWall(640, 100);
	GameEngine::GameObject* wallBottom = new GameEngine::FloorWall(640, 100);
	GameEngine::GameObject* bat1 = new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);
	GameEngine::GameObject* bat2= new GameEngine::GameObject(GameEngine::Coordinate::Z, 240, 160);


	wallBack->setPosition(GameEngine::Coordinate(-320, -240, 80));
	wallFront->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallLeft->setPosition(GameEngine::Coordinate(-320, -240, 0));
	wallRight->setPosition(GameEngine::Coordinate(320, -240, 0));
	wallTop->setPosition(GameEngine::Coordinate(-320, 240, 0));
	wallBottom->setPosition(GameEngine::Coordinate(-320, -240, 0));
	bat1->setPosition(GameEngine::Coordinate(0, 0, 8));
	bat2->setPosition(GameEngine::Coordinate(-100, -50, 72));

	engine->addObject(wallFront);
	engine->addObject(wallBack);
	engine->addObject(wallLeft);
	engine->addObject(wallRight);
	engine->addObject(wallTop);
	engine->addObject(wallBottom);
	engine->addObject(bat1);
	engine->addObject(bat2);

	return engine;
}

void EngineTest::GameField(int cicles, GameEngine::Coordinate speed) {
	int i;
	GameEngine::Engine* engine = getGameField();
	engine->getBall()->setPosition(GameEngine::Coordinate(-270, 0, 15));
	engine->getBall()->setSpeed(speed);

	for (i = 0; i < cicles; ++i) {
		engine->moveBall();
		std::cout << engine->getBall()->getPosition().getX() << ",";
		std::cout << engine->getBall()->getPosition().getY() << ",";
		std::cout << engine->getBall()->getPosition().getZ() << " ";

		std::cout << engine->getBall()->getSpeed().getX() << ",";
		std::cout << engine->getBall()->getSpeed().getY() << ",";
		std::cout << engine->getBall()->getSpeed().getZ() << std::endl;

		if (abs(engine->getBall()->getPosition().getX()) > 320){
			delete engine;
			fail("Out of field X");
		}
		if (abs(engine->getBall()->getPosition().getY()) > 240){
			delete engine;
			fail("Out of field Y");
		}
		if (engine->getBall()->getPosition().getZ() > 80 || engine->getBall()->getPosition().getZ() < 0){
			delete engine;
			fail("Out of field Z");
		}
	}

	delete engine;
}

bool EngineTest::test() {
	int i, j, k, m;
//	ZaxisOnly();

	GameField(1000, Coordinate(0, -3, 6));

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			for (k = 1; k < 7; ++k) {
//				for (m = 100; m < 1000; m+=100) {
					std::cout << "RUN " << m << " ((-)" << i << ", (-)" << j << ", " << k << ")" << std::endl;
					GameField(1000, Coordinate(i, j, k));
					std::cout << "--" << std::endl;
					GameField(1000, Coordinate(-i, j, k));
					std::cout << "--" << std::endl;
					GameField(1000, Coordinate(i, -j, k));
					std::cout << "--" << std::endl;
					GameField(1000, Coordinate(-i, -j, k));
//				}
			}
		}
	}
	return true;
}

} /* namespace GameEngine */
