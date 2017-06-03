/*
 * TestFailsException.cpp
 *
 *  Created on: 22 mei 2017
 *      Author: Acer
 */

#include <TestFailsException.h>

TestFailsException::TestFailsException(std::string message)
	: m_message(message)
{

}

TestFailsException::~TestFailsException() {
}

const char* TestFailsException::what() const throw () {
	return (std::string("Test has failed. Test message: ") + m_message).c_str();
}

const std::string& TestFailsException::getMessage() const {
	return m_message;
}
