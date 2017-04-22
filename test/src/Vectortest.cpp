/*
 * Vectortest.cpp
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#include <Vectortest.h>
#include <Vector.h>

#include <iostream>

Vector_test::Vector_test()
	: Test("Vector test")
{

}

Vector_test::~Vector_test() {

}

bool Vector_test::test(){
	add();
	get();
	remove();
	clear();
	inOtherFunction();
	return true;
}

void Vector_test::inOtherFunction(){
	Vector<int> obj;
	inOtherFunction_add(&obj);

	if (obj.length() != 2){
		fail("in_other_function: length");
	}
	if (obj[0] != 18){
		fail("in_other_function: 18");
	}
	if (obj[1] != 24){
		fail("in_other_function: 24");
	}
}

template <class T>
void Vector_test::inOtherFunction_add(Vector<T> *obj){
	int a = 18;
	int b = 85;
	int c = 24;
	obj->add(a);
	obj->add(b);
	obj->add(c);
	obj->remove(1);
}

void Vector_test::clear(){
	Vector<int> obj;
	int a = 12;
	int b = 98;

	obj.add(a);
	obj.add(b);

	obj.clear();
	if (obj.length() != 0){
		fail("Clear");
	}
}

void Vector_test::remove(){
	Vector<int> obj;
	int a = 12;
	int b = 98;

	obj.add(a);
	obj.add(b);
	obj.remove(0);

	if (obj.length() != 1){
		fail("remove: length");
	}
	if (obj[0] != b){
		fail("remove: next item");
	}
}

void Vector_test::get(){
	Vector<int> obj;
	int a = 8;
	int b = 58;

	obj.add(a);
	obj.add(b);

	if (obj[0] != a){
		fail("get: a");
	}
	if (obj[1] != b){
		fail("get:b ");
	}
}

void Vector_test::add(){
	Vector<int> obj;
	int a = 5;
	int b = 9;

	obj.add(a);
	if (obj.length() != 1){
		fail("add: length 1");
	}

	obj.add(b);
	if (obj.length() != 2){
		fail("add: length 2");
	}
}
