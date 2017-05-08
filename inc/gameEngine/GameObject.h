/*
 * Object.h
 *
 *  Created on: 5 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMEENGINE_OBJECT_H_
#define INC_GAMEENGINE_OBJECT_H_

#include <stdint.h>
#include <GameEngine/Coordinate.h>

namespace GameEngine {

class GameObject {
public:
								GameObject(Coordinate::AXIS compareAxis, uint8_t width, uint8_t height);
	virtual 					~GameObject();

public:
	virtual const bool			isCollided(const GameObject* with, const Coordinate &at) const;
	virtual Coordinate			distanceTo(const GameObject *object) const;

public:
	const Coordinate::AXIS 		getCompareAxis() const;

public:
	const Coordinate& 			getPosition() const;
	uint8_t 					getHeight() const;
	uint8_t 					getWidth() const;

	void 						setPosition(const Coordinate& position);

private:
	Coordinate					m_position;
	const Coordinate::AXIS		m_compareAxis;
	uint8_t						m_width, m_height;
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_OBJECT_H_ */
