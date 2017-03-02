//
// Created by Acer on 2-3-2017.
//

#ifndef TESTING_CONSOLE_ASCII_H
#define TESTING_CONSOLE_ASCII_H

#include <iostream>

#define cout std::cout

class Console_ASCII {
//constructors
public:
					Console_ASCII();
	virtual         ~Console_ASCII();

public:
	//cursor manipulation
	virtual void    setCursor(int x, int y);
	virtual void    saveCursor();
	virtual void    restoreCursor();

	//colors
	virtual void    setForeGroundColor(int color);
	virtual void    setBackGroundColor(int color);

//members variables
private:
	void            printEscape();
};


#endif //TESTING_CONSOLE_ASCII_H
