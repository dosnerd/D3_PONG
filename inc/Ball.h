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

#ifndef TESTING_BALL_H
#define TESTING_BALL_H


#include <Coordinates.h>
#include <MVC/Model.h>

class Ball : public MVC::Model{
//constructors
public:
								Ball();
								Ball(int x, int y, int z);
								Ball(int x, int y, int z, int dX, int dY, int dZ);
	virtual                     ~Ball();

//getters
public:
	virtual const Coordinates   &getPosition() const;
	virtual const Coordinates   getDeltaAsCoordinates() const;
	virtual int                 getDeltaX() const;
	virtual int                 getDeltaY() const;
	virtual int                 getDeltaZ() const;

//setters
public:
	virtual void                setPosition(int x, int y, int z);
	virtual void                setDeltaX(int deltaX);
	virtual void                setDeltaY(int deltaY);
	virtual void                setDeltaZ(int deltaZ);

//members variables
private:
	Coordinates                 position;
	int                         deltaX, deltaY, deltaZ;
};


#endif //TESTING_BALL_H
