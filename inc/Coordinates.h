//
// Created by Acer on 2-3-2017.
//

#ifndef TESTING_COORDINATES_H
#define TESTING_COORDINATES_H


class Coordinates {
//constructors
public:
					Coordinates(int x = 0, int y = 0, int z = 0);
	virtual         ~Coordinates();

//getters
public:
	virtual int     getX() const;
	virtual int     getY() const;
	virtual int     getZ() const;

//setters
public:
	virtual void    setX(int x);
	virtual void    setY(int y);
	virtual void    setZ(int z);

//Member variables
private:
	int             x, y, z;
};


#endif //TESTING_COORDINATES_H
