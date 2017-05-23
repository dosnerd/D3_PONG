/*
 * dac_sound.h
 *
 *  Created on: May 22, 2017
 *      Author: Rick
 */

#ifndef INC_MDAC_H_
#define INC_MDAC_H_

#include <Stream.h>
#include <Vector.h>
#include <config_file.h>

class MDAC  {
public:

	virtual 				~MDAC();
	void 					setData(uint16_t data);
	uint16_t 				getChannel1Data(void);
	static MDAC*			getInstance();

private:
							MDAC();
	static MDAC				sInstance;
	void					GPIOinit();
	void 					DACinit();

	// void GPIOinit();

};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_MDAC_H_ */

// public:



	// virtual void			write(uint16_t data);
	// virtual const uint16_t	read();

// public:
	// virtual const uint16_t	getBufferLenght() const;
	// static DAC				*getInstance();

// private:
	// static DAC				sInstance;
	// Vector<uint16_t>		m_buffer;

	// void 					GPIOinit();
	// void 					GPIOconfig();
	// void 					DACinit();
// };

/*#if SPI_INTERRUPT_ENABLE
public:
	//virtual void 			interruptRead();

private:
	// void 					DACinterruptConfig(); // Do dac's even have interrupts?

#endif
};*/

//#ifdef __cplusplus
//extern "C" {
//#endif
//// #if SPI_INTERRUPT_ENABLE
//
//// void SPI2_IRQHandler();
//
//// #endif /* SPI_INTERRUPT_ENABLE */
////#ifdef __cplusplus
////}
//#endif

