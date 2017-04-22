/*
 * Vectortest.h
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#ifndef TEST_INC_VECTORTEST_H_
#define TEST_INC_VECTORTEST_H_

#include <Test.h>

template <class T>
class Vector;

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
	void					inOtherFunction();

	template <class T>
	void					inOtherFunction_add(Vector<T> *obj);
};

#endif /* TEST_INC_VECTORTEST_H_ */
