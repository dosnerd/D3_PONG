/*
 * ConsoleASCIIcode.cpp
 *
 *  Created on: 22 mei 2017
 *      Author: Acer
 */

#include <ConsoleASCIIcode.h>

#define ESCAPE_SEQUENCE (char)0x1B, (char)0x5B

std::string ConsoleASCIIcode::getForegroundSequence(char color) {
	std::string sequence({ESCAPE_SEQUENCE});
	sequence += std::to_string(color + 30);
	sequence += 'm';
	return sequence;
}

ConsoleASCIIcode::ConsoleASCIIcode() {
}

ConsoleASCIIcode::~ConsoleASCIIcode() {
}

