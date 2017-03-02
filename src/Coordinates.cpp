//
// Created by Acer on 2-3-2017.
//

#include "Coordinates.h"

Coordinates::Coordinates(int x, int y, int z)
		: x(x), y(y), z(z) {

}

Coordinates::~Coordinates() {

}

int Coordinates::getX() const {
	return x;
}

int Coordinates::getY() const {
	return y;
}

int Coordinates::getZ() const {
	return z;
}

void Coordinates::setX(int x) {
	Coordinates::x = x;
}

void Coordinates::setY(int y) {
	Coordinates::y = y;
}

void Coordinates::setZ(int z) {
	Coordinates::z = z;
}
