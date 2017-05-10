/*
 * Test.cpp
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#include <Test.h>
#include <Memoryleak.h>
#include <iostream>
#include <Windows.h>

Test::Test(std::string name)
	: m_failed(false)
	, m_name(name)
{
}

Test::~Test() {
}

void Test::run(){
	FILETIME ftStart, ftEnd;
	double dElapsed;

	try{
		::GetSystemTimeAsFileTime(&ftStart);
		m_failed = !test();
		::GetSystemTimeAsFileTime(&ftEnd);
	}
	catch (std::exception &e) {
		::GetSystemTimeAsFileTime(&ftEnd);

		std::cout << "Error has occurd" << std::endl;
		m_failed = true;
	}

	if (m_failed){
		std::cout << m_name << ": failed (";
	} else {
		std::cout << m_name << ": succeed (";
	}

	dElapsed = (ftEnd.dwLowDateTime - ftStart.dwLowDateTime) / 10000.0;
	std::cout << dElapsed << " ms)" << std::endl;
}

void Test::fail(std::string message){
	m_failed = true;
	std::cerr << "Failed: " << m_name << ": " << message << std::endl;
	throw std::exception();
}
