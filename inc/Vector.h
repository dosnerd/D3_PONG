/*
 * vector.h
 *
 *  Created on: 20 apr. 2017
 *      Author: Acer
 */

#ifndef INC_VECTOR_H_
#define INC_VECTOR_H_

#include <stdint.h>

template <class T>
class Vector {
public:
							Vector();
	virtual 				~Vector();

public:
	virtual T				&operator[](uint16_t index);

public:
	virtual void			add(T &item);
	virtual void			remove(uint16_t index);
	virtual void			clear();
	virtual const uint16_t	length() const;

private:
	T						*m_objects;
	uint8_t					m_nObjects;
};

#endif /* INC_VECTOR_H_ */
