/*
 * Buttons.h
 *
 *  Created on: 31 mei 2017
 *      Author: Acer
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

class Buttons {
public:
								Buttons();
	virtual 					~Buttons();

public:
	virtual bool				getButton();
	static Buttons				*getInstace();

private:
	static Buttons				sInstance;
};

#endif /* INC_BUTTONS_H_ */
