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

#ifndef TESTING_CONSOLE_ASCII_H
#define TESTING_CONSOLE_ASCII_H

#include <iostream>

#define cout std::cout

class Console_ASCII {
//emum
public:
	enum Colors {
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
	};

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
