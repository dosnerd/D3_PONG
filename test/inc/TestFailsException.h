/*
 * TestFailsException.h
 *
 *  Created on: 22 mei 2017
 *      Author: Acer
 */

#ifndef TEST_INC_TESTFAILSEXCEPTION_H_
#define TEST_INC_TESTFAILSEXCEPTION_H_

#include <exception>
#include <string>

class TestFailsException: public std::exception {
public:
									TestFailsException(std::string message);
	virtual 						~TestFailsException();

	const char 						*what () const throw ();
	const std::string& 				getMessage() const;

private:
	std::string 					m_message;
};

#endif /* TEST_INC_TESTFAILSEXCEPTION_H_ */
