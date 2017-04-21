/*
 * Test.h
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_TEST_H_
#define TEST_INC_TEST_H_

class Test {
public:
							Test();
	virtual					~Test();

public:
	virtual bool			run();
	virtual bool			test() = 0;

protected:
	virtual void			fail();

private:
	bool 					m_failed;
};

#endif /* TEST_INC_TEST_H_ */
