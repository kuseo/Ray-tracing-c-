#ifndef __POLYGON_H__
#define __POLYGON_H__

#include "Object.h"
class Polygon : public Object
{
public:
	/*
	member variables
	*/
	VECTOR3D a, b, c;
	VECTOR3D alpha, beta, gamma;

	/*
		constructor
	*/
	Polygon() {}

	/*
	destructor
	*/
	virtual ~Polygon() {}

	/*
	member function
	*/
	void varicentric(Ray r)
	{

	}

	virtual bool hit(Ray r, float *t)
	{

	}

	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray)
	{

	}

	virtual VECTOR3D get_normal(VECTOR3D point)
	{

	}

	virtual VECTOR3D get_normal()
	{

	}
};

#endif // __POLYGON_H__
