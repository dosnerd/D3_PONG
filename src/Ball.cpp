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

#include "Ball.h"

//CONSTRUCTORS
Ball::Ball()
		: Ball(0, 0, 0, 1, 1, 1) {

}

Ball::Ball(int x, int y, int z)
		: Ball(x, y, x, 1, 1, 1) {

}

Ball::Ball(int x, int y, int z, int dX, int dY, int dZ)
		: position(x, y, z), deltaX(dX), deltaY(dY), deltaZ(dZ) {

}

Ball::~Ball() {

}


//GETTERS

const Coordinates &Ball::getPosition() const {
	return position;
}

int Ball::getDeltaX() const {
	return deltaX;
}

int Ball::getDeltaY() const {
	return deltaY;
}

int Ball::getDeltaZ() const {
	return deltaZ;
}

const Coordinates Ball::getDeltaAsCoordinates() const {
	return Coordinates(deltaX, deltaY, deltaZ);
}

//SETTERS

void Ball::setPosition(int x, int y, int z) {
	Ball::position.setX(x);
	Ball::position.setY(y);
	Ball::position.setZ(x);
	notify();
}

void Ball::setDeltaX(int deltaX) {
	Ball::deltaX = deltaX;
	notify();
}

void Ball::setDeltaY(int deltaY) {
	Ball::deltaY = deltaY;
	notify();
}

void Ball::setDeltaZ(int deltaZ) {
	Ball::deltaZ = deltaZ;
	notify();
}
