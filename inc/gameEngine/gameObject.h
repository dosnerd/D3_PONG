/*
 * Object.h
 *
 *  Created on: 5 mei 2017
 *      Author: Acer
 */

#ifndef INC_GAMEENGINE_OBJECT_H_
#define INC_GAMEENGINE_OBJECT_H_

#include <stdint.h>

class Coordinate;
namespace GameEngine {

class gameObject {
public:
								gameObject(uint8_t width, uint8_t height);
	virtual 					~gameObject();

public:
	virtual const bool			isCollided(gameObject* with, Coordinate at);
	virtual const Coordinate	distanceTo(gameObject *object);

private:
	Coordinate					*m_location;
	uint8_t						m_width, m_height;

};

} /* namespace GameEngine */

#endif /* INC_GAMEENGINE_OBJECT_H_ */
