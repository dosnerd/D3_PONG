/*
 * ConsoleASCIIcode.h
 *
 *  Created on: 22 mei 2017
 *      Author: Acer
 */

#ifndef TEST_INC_CONSOLEASCIICODE_H_
#define TEST_INC_CONSOLEASCIICODE_H_

#include <string>

class ConsoleASCIIcode {
public:
	enum Colors {
		BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
	};

public:
	static std::string			getForegroundSequence(char color);
private:
								ConsoleASCIIcode();
	virtual 					~ConsoleASCIIcode();
};

#endif /* TEST_INC_CONSOLEASCIICODE_H_ */
