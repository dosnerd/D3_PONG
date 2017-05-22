/*
 * DemoTest.cpp
 *
 *  Created on: 22 mei 2017
 *      Author: Acer
 */

#include <GameControllers/DemoTest.h>
#include <GameControllers/DemoImpl.h>
#include <gameEngine/Engine.h>

namespace GameControllers {

DemoTest::DemoTest()
	: Test("Demo controller")
{
}

DemoTest::~DemoTest() {
}

void DemoTest::dummyTest(uint32_t ticks) {
	uint32_t i, scoreP1 = 0, scoreP2 = 0;
	std::string logMsg;
	GameEngine::Engine* engine = new GameEngine::Engine();
	GameControllers::DemoImpl controller(engine->getBall());

	controller.setupField(engine);

	for (i = 0; i < ticks; ++i) {
		engine->moveBall();
		MVC::Observer::handleNotifications();
	}

	for (i = 0; i < controller.getStats().length(); ++i) {
		if (controller.getStats()[i] == 1)
			scoreP1++;
		else if (controller.getStats()[i] == 2)
			scoreP2++;
	}

	appendToResultMessage("Dummy test: \n");
	appendToResultMessage("\tTicks: " + std::to_string(ticks) + "\n");
	appendToResultMessage("\tScore player 1: " + std::to_string(scoreP1) + "\n");
	appendToResultMessage("\tScore player 2: " + std::to_string(scoreP2) + "\n");


	delete engine;
}

bool DemoTest::test() {
	dummyTest(100000);
	return true;
}

} /* namespace GameControllers */
