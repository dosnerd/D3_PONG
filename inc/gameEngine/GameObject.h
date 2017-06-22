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

#define GAMEOBJECT_BOUNCE_EFFECT_LEFT	0x1
#define GAMEOBJECT_BOUNCE_EFFECT_RIGHT	0x2
#define GAMEOBJECT_BOUNCE_EFFECT_TOP	0x4
#define GAMEOBJECT_BOUNCE_EFFECT_BOTTOM	0x8

namespace GameEngine {

class GameObject {
public:
								GameObject(Coordinate::AXIS compareAxis, int32_t width, int32_t height);
	virtual 					~GameObject();

public:
	virtual const bool			isCollided(const GameObject* with, const Coordinate &at) const;
	virtual Coordinate			distanceTo(const GameObject *object) const;

public:
	virtual const uint8_t		getEffectSides(const GameObject* with, const Coordinate &at) const;
	const Coordinate::AXIS 		getCompareAxis() const;
	const Coordinate& 			getPosition() const;
	int32_t 					getHeight() const;
	int32_t 					getWidth() const;

	void 						setPosition(const Coordinate& position);

private:
	Coordinate					m_position;
	const Coordinate::AXIS		m_compareAxis;
	int32_t						m_width, m_height;
};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_OBJECT_H_ */
