/*
 * Created by David de Prez on 2-3-2017.
 *
 * 3D pong is a game console to play the game PONG in 3D.
 *  Copyright (C) 2017  David de Prez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
