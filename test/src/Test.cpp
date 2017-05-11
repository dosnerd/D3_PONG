/*
 * Test.cpp
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#include <Test.h>
#include <Memoryleak.h>
#include <iostream>

Test::Test(std::string name)
	: m_failed(false)
	, m_name(name)
{
}

Test::~Test() {
}

void Test::run(){
	try{
		test();
	}
	catch (std::exception &e) {
		std::cout << "Error has occurd" << std::endl;
		m_failed = true;
	}

	if (m_failed){
		std::cout << m_name << ": failed" << std::endl;
	} else {
		std::cout << m_name << ": succeed" << std::endl;
	}
}

void Test::fail(std::string message){
	m_failed = true;
	std::cerr << "Failed: " << m_name << ": " << message << std::endl;
	throw std::exception();
}
