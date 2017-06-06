/*
 * Stream.h
 *
 *  Created on: 20 apr. 2017
 *      Author: Acer
 */

#ifndef INC_STREAM_H_
#define INC_STREAM_H_

#include <stdint.h>
#include <MVC/Model.h>

class Stream : public MVC::Model {
public:
							Stream() { }
	virtual 				~Stream() { }

public:
	virtual void			write(uint16_t data) = 0;
	virtual const uint16_t	read() = 0;

public:
	virtual const uint16_t	getBufferLenght() const = 0;

};

#endif /* INC_STREAM_H_ */
