/*
 * main.cpp
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */
#include <iostream>
#include <Memoryleak.h>
#include <Test.h>
#include <Vectortest.h>
#include <gameEngine/CoordinateTest.h>
#include <gameEngine/GameObjectTest.h>
#include <gameEngine/EngineTest.h>
#include <MVCtest.h>
#include <GameControllers/DemoTest.h>
#include <thread>
#include <string.h>

void *operator new(std::size_t size){
	return Memory_leak::current.reserve(size);
}

void operator delete(void *ptr) noexcept
{
	Memory_leak::current.free(ptr);
}

Memory_leak Memory_leak::current;
int main(int argc, char *argv[]){
	if (Memory_leak::current.check()){
		std::cout << "Startup have reserved dynamic memory" << std::endl;
	} else
		std::cout << "Clean dynamic memory startup" << std::endl;

	std::cout << "Start test..." << std::endl;
	unsigned int i;
	bool threads = argc > 1 && std::string(argv[1]) == "-t";

	if (threads)
		std::cout << "Using threads" << std::endl;
	else
		std::cout << "No threads" << std::endl;

	Test *a[] = {
			new Vector_test(),
			new MVCtest(),
			new GameControllers::DemoTest(),
			new GameEngine::EngineTest(),
			new GameEngine::CoordinateTest(),
			new GameEngine::GameObjectTest(),
	};
	std::thread tests[sizeof(a) / sizeof(Test *)];

	for (i = 0; i < sizeof(a) / sizeof(Test *); ++i) {
		if (threads)
			tests[i] = std::thread(&Test::run, a[i]);
		else
			a[i]->run();
	}

	//delete tests
	for (i = 0; i < sizeof(a) / sizeof(Test *); ++i) {
		if (threads)
			tests[i].join();
		delete a[i];
	}

	MVC::Observer::emptyContainer();
	if (Memory_leak::current.check()){
		std::cout << "One or more test has memory leaks";
	} else {
		std::cout << "All runned test passed memory leak test" << std::endl;
	}

	return 0;
}
