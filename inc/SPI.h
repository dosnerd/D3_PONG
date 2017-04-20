/*
 * SPI.h
 *
 *  Created on: 20 apr. 2017
 *      Author: Acer
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include <Stream.h>
#include <Vector.h>

class SPI : Stream {
public:
							SPI();
	virtual 				~SPI();

public:
	virtual void			write(uint16_t data);
	virtual const uint16_t	read();

public:
	virtual const uint16_t	getBufferLenght() const;

private:
	Vector<uint16_t>		m_buffer;
};

#endif /* INC_SPI_H_ */
