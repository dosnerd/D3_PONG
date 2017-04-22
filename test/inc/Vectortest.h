/*
 * Vectortest.h
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_VECTORTEST_H_
#define TEST_INC_VECTORTEST_H_

#include <Test.h>

class Vector_test: public Test {
public:
							Vector_test();
	virtual 				~Vector_test();

public:
	virtual bool			test();

private:
	void					add();
	void					get();
	void					remove();
	void					clear();
};

#endif /* TEST_INC_VECTORTEST_H_ */
