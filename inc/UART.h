/*
 * UART.h
 *
 *  Created on: 22 apr. 2017
 *      Author: Acer
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <Stream.h>
#include <Vector.h>
#include <config_file.h>

class UART: public Stream {
public:
								UART();
	virtual 					~UART();

public:
	virtual void				write(uint16_t data);
	virtual const uint16_t		read();

public:
	virtual const uint16_t		getBufferLenght() const;

public:
#if UART_INTERRUPT_ENABLE
	virtual void				interruptRead();
	static UART					sInstance;
#endif

private:
	Vector<uint16_t>			m_buffer;
};

#ifdef __cplusplus
extern "C" {
#endif

#if UART_INTERRUPT_ENABLE

void UART4_IRQHandler();

#endif /* SPI_INTERRUPT_ENABLE */
#ifdef __cplusplus
}
#endif
#endif /* INC_UART_H_ */
