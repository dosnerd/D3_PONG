/*
 * main.cpp
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */
#include <iostream>
#include <Memoryleak.h>

void *operator new(std::size_t size){
	return Memory_leak::current.reserve(size);
}

void operator delete(void *ptr) noexcept
{
	Memory_leak::current.free(ptr);
}

Memory_leak Memory_leak::current;
int main(int argc, char **argv){
	std::cout << "Start test..." << std::endl;


	if (Memory_leak::current.check()){
		std::cout << "One or more test has memory leaks";
	} else {
		std::cout << "All test passed" << std::endl;
	}
	return 0;
}
