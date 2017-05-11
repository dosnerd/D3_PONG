/*
 * Coordinates.h
 *
 *  Created on: 5 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMEENGINE_COORDINATE_H_
#define INC_GAMEENGINE_COORDINATE_H_

#include <stdint.h>
#define FIXED_POINT_MULTILIER 1000000

namespace GameEngine {

class Coordinate {
public:
								Coordinate();
								Coordinate(int32_t x, int32_t y, int32_t z);
	virtual						~Coordinate();

public:
	enum AXIS { NONE, X, Y, Z };

public:
//	virtual Coordinate			transform(float factor, const Coordinate *delta) const;
	virtual void				flip(Coordinate::AXIS axis);

public:
	virtual Coordinate			operator-(const Coordinate &coordinate) const;
	virtual Coordinate			operator+(const Coordinate &coordinate) const;
	virtual Coordinate			operator*(int32_t number) const;
	virtual Coordinate			operator/(int32_t number) const;

public:
	int32_t 						get(Coordinate::AXIS axis) const;
	int32_t 						getX() const;
	int32_t 						getY() const;
	int32_t 						getZ() const;

public:
	void	 					set(Coordinate::AXIS axis, int32_t value);
	void 						setX(int32_t x);
	void 						setY(int32_t y);
	void 						setZ(int32_t z);

private:
	int32_t						m_x, m_y, m_z;

	int32_t 					roundNumber(int32_t number) const;
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_COORDINATE_H_ */
