/*
 * Coordinates.cpp
 *
 *  Created on: 5 mei 2017
 *      Author: Acer
 */

#include <gameEngine/Coordinate.h>

namespace GameEngine {

Coordinate::Coordinate()
	: m_x(0), m_y(0), m_z(0) { }

Coordinate::Coordinate(int8_t x, int8_t y, int8_t z)
	: m_x(x), m_y(y), m_z(z) { }

Coordinate::~Coordinate() {

}

Coordinate Coordinate::transform(float factor, const Coordinate *delta) const {
	return (*delta * factor) + *this;
}

Coordinate Coordinate::operator -(const Coordinate& coordinate) const {
	return Coordinate(
					m_x - coordinate.m_x,
					m_y - coordinate.m_y,
					m_z - coordinate.m_z
				);
}

Coordinate Coordinate::operator +(const Coordinate& coordinate) const {
	return Coordinate(
				m_x + coordinate.m_x,
				m_y + coordinate.m_y,
				m_z + coordinate.m_z
			);
}

Coordinate Coordinate::operator *(float number) const {
	return Coordinate(
					m_x * number,
					m_y * number,
					m_z * number
				);
}

int8_t Coordinate::getX() const {
	return m_x;
}

int8_t Coordinate::getY() const {
	return m_y;
}

int8_t Coordinate::getZ() const {
	return m_z;
}

void Coordinate::set(Coordinate::AXIS axis, int8_t value) {
	switch (axis){
	case X:
		return setX(value);
	case Y:
		return setY(value);
	default:
		return setZ(value);
	}
}

void Coordinate::setX(int8_t x) {
	this->m_x = x;
}

void Coordinate::setY(int8_t y) {
	this->m_y = y;
}

void Coordinate::flip(Coordinate::AXIS axis) {
	set(axis, -get(axis));
}

void Coordinate::setZ(int8_t z) {
	this->m_z = z;
}

} /* namespace GameEngine */

int8_t GameEngine::Coordinate::get(Coordinate::AXIS axis) const {
	switch (axis){
	case X:
		return getX();
	case Y:
		return getY();
	default:
		return getZ();
	}
}
