/*
 * main.cpp
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */
#include <iostream>
#include <Memoryleak.h>
#include <Vectortest.h>
#include <gameEngine/CoordinateTest.h>
#include <gameEngine/GameObjectTest.h>
#include <gameEngine/EngineTest.h>
#include <MVCtest.h>
#include <thread>

void *operator new(std::size_t size){
	return Memory_leak::current.reserve(size);
}

void operator delete(void *ptr) noexcept
{
	Memory_leak::current.free(ptr);
}

Memory_leak Memory_leak::current;
int main(){
	std::cout << "Start test..." << std::endl;

	unsigned int i;
	Test *a[] = {
			new Vector_test(),
			new MVCtest(),
			new GameEngine::EngineTest(),
			new GameEngine::CoordinateTest(),
			new GameEngine::GameObjectTest(),
	};
	std::thread tests[sizeof(a) / sizeof(Test *)];

	for (i = 0; i < sizeof(a) / sizeof(Test *); ++i) {
		tests[i] = std::thread(&Test::run, a[i]);
//		a[i]->run();
	}

	//delete tests
	for (i = 0; i < sizeof(a) / sizeof(Test *); ++i) {
		tests[i].join();
		delete a[i];
	}

	if (Memory_leak::current.check()){
		std::cout << "One or more test has memory leaks";
	} else {
		std::cout << "All runned test passed memory leak test" << std::endl;
	}
	return 0;
}
