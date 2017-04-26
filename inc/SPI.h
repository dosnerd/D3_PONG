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
#include <config_file.h>

class SPI : Stream {
public:
	virtual 				~SPI();

private:
							SPI();

public:
	virtual void			write(uint16_t data);
	virtual const uint16_t	read();

public:
	virtual const uint16_t	getBufferLenght() const;
	static SPI				*getInstance();

private:
	static SPI				sInstance;
	Vector<uint16_t>		m_buffer;

	void 					GPIOinit();
	void 					GPIOconfig();
	void 					SPIinit();

#if SPI_INTERRUPT_ENABLE
public:
	virtual void 			interruptRead();

private:
	void 					SPIinterruptConfig();

#endif
};

#ifdef __cplusplus
extern "C" {
#endif
#if SPI_INTERRUPT_ENABLE

void SPI2_IRQHandler();

#endif /* SPI_INTERRUPT_ENABLE */
#ifdef __cplusplus
}
#endif
#endif /* INC_SPI_H_ */
