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
	void 					DACinit(uint32_t channel);

	// void GPIOinit();

};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_MDAC_H_ */
