/*
 * Test.h
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_TEST_H_
#define TEST_INC_TEST_H_

#include <string>
#include <mutex>
#include <iostream>

class Test {
public:
							Test(std::string name);
	virtual					~Test();

public:
	virtual void			run();
	virtual bool			test() = 0;

public:
 	const std::string& 		getName() const;


protected:
	template <class T>
	void					log(T message);
	virtual void			fail(std::string message);

	template <class T>
	void					failIfDifferent(T value, T expected, std::string message);
	template <class T>
	void					failIfEqual(T value, T expected, std::string message);

	void					printResults();
	void					appendToResultMessage(std::string message);

private:
	static std::mutex		sLogMutex;
	bool 					m_failed;
	std::string				m_name, m_resultMessage;
};

/*
 * Must include for implementations with templates.
 */
#include "../src/Test.hpp"

#endif /* TEST_INC_TEST_H_ */
