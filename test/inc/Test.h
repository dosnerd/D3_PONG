/*
 * Test.h
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_TEST_H_
#define TEST_INC_TEST_H_

#include <string>
//#include <mutex>

class Test {
public:
							Test(std::string name);
	virtual					~Test();

public:
	virtual void			run();
	virtual bool			test() = 0;

protected:
	virtual void			fail(std::string message);

private:
	bool 					m_failed;
	std::string				m_name;
};

#endif /* TEST_INC_TEST_H_ */
