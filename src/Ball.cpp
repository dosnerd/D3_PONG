//
// Created by Acer on 2-3-2017.
//

#include "Ball.h"

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

void Ball::setPosition(int x, int y, int z) {
	Ball::position.setX(x);
	Ball::position.setY(y);
	Ball::position.setZ(x);
}

void Ball::setDeltaX(int deltaX) {
	Ball::deltaX = deltaX;
}

void Ball::setDeltaY(int deltaY) {
	Ball::deltaY = deltaY;
}

void Ball::setDeltaZ(int deltaZ) {
	Ball::deltaZ = deltaZ;
}
