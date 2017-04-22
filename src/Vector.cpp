/*
 * vector.cpp
 *
 *  Created on: 20 apr. 2017
 *      Author: Acer
 */

#include <Vector.h>

template<class T>
Vector<T>::Vector() :
		m_nObjects(0) {
	m_objects = new T[m_nObjects];
}

template<class T>
Vector<T>::~Vector() {
	delete[] m_objects;
}

template<class T>
T &Vector<T>::operator [](uint16_t index) {
	if (index < m_nObjects) {
		return m_objects[index];
	} else {
		return m_objects[0];
	}
}

template<class T>
void Vector<T>::add(T &item) {
	uint16_t i;
	T *old = m_objects;
	T *update = new T[m_nObjects + 1];

	//copy array
	for (i = 0; i < m_nObjects; ++i) {
		update[i] = old[i];
	}

	//add new item
	update[m_nObjects++] = item;

	//clean up
	m_objects = update;
	delete[] old;
}

template<class T>
void Vector<T>::remove(uint16_t index) {
	uint16_t i;

	T *old = m_objects;
	T *update = new T[m_nObjects - 1];

	//check if index is valid
	if (index >=m_nObjects){
		delete[] update;
		return;
	}

	//copy all except index
	for (i = 0; i < index; ++i) {
		update[i] = old[i];
	}
	for (i = index + 1; i < m_nObjects; ++i) {
		update[i - 1] = old[i];
	}

	//clean up
	m_nObjects--;
	m_objects = update;
	delete[] old;
}

template <class T>
void Vector<T>::clear(){
	T *old = m_objects;

	//clear list
	m_nObjects = 0;
	m_objects = new T[0];
	delete[] old;
}

template<class T>
const uint16_t Vector<T>::length() const {
	return m_nObjects;
}

template class Vector<uint16_t>;
template class Vector<int>;
