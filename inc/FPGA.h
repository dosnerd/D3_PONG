/*
 * FPGA.h
 *
 *  Created on: 25 apr. 2017
 *      Author: Acer
 */

#ifndef INC_FPGA_H_
#define INC_FPGA_H_

class FPGA {
public:
	virtual 					~FPGA();

private:
								FPGA();

public:
	virtual void				turnOn();
	virtual void				turnOff();

public:
	static FPGA					*getInstance();

private:
	static FPGA					sInstance;

	void 						GPIOinit();

public:
	//static FPGA					sInstance;
};

#endif /* INC_FPGA_H_ */
