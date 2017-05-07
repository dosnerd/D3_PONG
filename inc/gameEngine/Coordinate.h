/*
 * Coordinates.h
 *
 *  Created on: 5 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMEENGINE_COORDINATE_H_
#define INC_GAMEENGINE_COORDINATE_H_

#include <stdint.h>

namespace GameEngine {

class Coordinate {
public:
								Coordinate();
								Coordinate(uint8_t x, uint8_t y, uint8_t z);
	virtual						~Coordinate();

public:
	virtual Coordinate			transform(float factor, const Coordinate *delta) const;

public:
	virtual Coordinate			operator-(const Coordinate &coordinate) const;
	virtual Coordinate			operator+(const Coordinate &coordinate) const;
	virtual Coordinate			operator*(float number) const;


public:
	uint8_t 					getX() const;
	uint8_t 					getY() const;
	uint8_t 					getZ() const;

public:
	void 						setX(uint8_t x);
	void 						setY(uint8_t y);
	void 						setZ(uint8_t z);

private:
	uint8_t						m_x, m_y, m_z;
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_COORDINATE_H_ */
