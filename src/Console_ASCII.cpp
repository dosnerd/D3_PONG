//
// Created by Acer on 2-3-2017.
//

#include "Console_ASCII.h"

Console_ASCII::Console_ASCII() { }

Console_ASCII::~Console_ASCII() {

}

void Console_ASCII::printEscape() {
	cout << (char) 0x1B << (char) 0x5B;
}

void Console_ASCII::setCursor(int x, int y) {
	printEscape();
	cout << std::to_string(x) << ";";
	cout << std::to_string(y);

	cout << "H";
}

void Console_ASCII::saveCursor() {
	printEscape();
	cout << 's';
}


void Console_ASCII::restoreCursor() {
	printEscape();
	cout << 'u';
}

void Console_ASCII::setForeGroundColor(int color) {
	printEscape();
	cout << std::to_string(color + 30) << 'm';
}

void Console_ASCII::setBackGroundColor(int color) {
	printEscape();
	cout << std::to_string(color + 40) << 'm';
}
