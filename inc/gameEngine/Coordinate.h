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
								Coordinate(int8_t x, int8_t y, int8_t z);
	virtual						~Coordinate();

public:
	enum AXIS { NONE, X, Y, Z };

public:
	virtual Coordinate			transform(float factor, const Coordinate *delta) const;
	virtual void				flip(Coordinate::AXIS axis);

public:
	virtual Coordinate			operator-(const Coordinate &coordinate) const;
	virtual Coordinate			operator+(const Coordinate &coordinate) const;
	virtual Coordinate			operator*(float number) const;

public:
	int8_t 						get(Coordinate::AXIS axis) const;
	int8_t 						getX() const;
	int8_t 						getY() const;
	int8_t 						getZ() const;

public:
	void	 					set(Coordinate::AXIS axis, int8_t value);
	void 						setX(int8_t x);
	void 						setY(int8_t y);
	void 						setZ(int8_t z);

private:
	int8_t						m_x, m_y, m_z;
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_COORDINATE_H_ */
