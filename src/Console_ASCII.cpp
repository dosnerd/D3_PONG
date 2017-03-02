//
// Created by Acer on 2-3-2017.
//

#include "Console_ASCII.h"

Console_ASCII::Console_ASCII() { }

Console_ASCII::~Console_ASCII() { }

void Console_ASCII::printEscape() {
	//write escape sequence to write a 'commando'
	cout << (char) 0x1B << (char) 0x5B;
}

void Console_ASCII::setCursor(int x, int y) {
	//esc[#;#h (x,y)
	printEscape();
	cout << std::to_string(x) << ";";
	cout << std::to_string(y);

	cout << "H";
}

void Console_ASCII::saveCursor() {
	//esc[s
	printEscape();
	cout << 's';
}


void Console_ASCII::restoreCursor() {
	//esc[u
	printEscape();
	cout << 'u';
}

void Console_ASCII::setForeGroundColor(int color) {
	//esc[#m (color: 30 <= c <= 37)
	printEscape();
	cout << std::to_string(color + 30) << 'm';
}

void Console_ASCII::setBackGroundColor(int color) {
	//esc[#m (color: 40 <= c <= 47)
	printEscape();
	cout << std::to_string(color + 40) << 'm';
}
