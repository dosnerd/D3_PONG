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
#include <stm32f4xx_conf.h>

class UART: public Stream {
public:
	virtual 					~UART();

private:
								UART(USART_TypeDef* USARTx);
								UART(UART &item);
								UART(UART &&item);

public:
	virtual void				write(uint16_t data);
	virtual const uint16_t		read();

public:
	virtual const uint16_t		getBufferLenght() const;
	static UART					*getInstance(uint8_t port);

#if UART_INTERRUPT_ENABLE
public:
	virtual void				interruptRead();

private:
	void 						UARTinterruptConfig();
#endif

private:
	USART_TypeDef* 				m_USARTx;
	Vector<uint16_t>			m_buffer;
	static UART					sInstance2, sInstance4;

private:
	void 						GPIOinit();
	void 						GPIOconfig();
	void 						UARTinit();
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
