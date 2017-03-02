//
// Created by Acer on 2-3-2017.
//

#ifndef TESTING_BALL_H
#define TESTING_BALL_H


#include <Coordinates.h>
class Ball {
//constructors
public:
								Ball();
								Ball(int x, int y, int z);
								Ball(int x, int y, int z, int dX, int dY, int dZ);
	virtual                     ~Ball();

//getters
public:
	virtual const Coordinates   &getPosition() const;
	virtual const Coordinates   getDeltaAsCoordinates() const;
	virtual int                 getDeltaX() const;
	virtual int                 getDeltaY() const;
	virtual int                 getDeltaZ() const;

//setters
public:
	virtual void                setPosition(int x, int y, int z);
	virtual void                setDeltaX(int deltaX);
	virtual void                setDeltaY(int deltaY);
	virtual void                setDeltaZ(int deltaZ);

//members variables
private:
	Coordinates                 position;
	int                         deltaX, deltaY, deltaZ;
};


#endif //TESTING_BALL_H
