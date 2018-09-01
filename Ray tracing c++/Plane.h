#ifndef __PLANE_H__
#define __PLANE_H__

#include "Object.h"

class Plane : public Object
{
public:

	/*
	member variables
	*/
	VECTOR3D normal;
	VECTOR3D dot;

	/*
	constructor
	*/
	Plane() {}
	Plane(VECTOR3D normal, VECTOR3D dot) : normal(normal), dot(dot) {}

	/*
	destructor
	*/
	virtual ~Plane() {}

	/*
	member function
	*/
	virtual bool hit(Ray r, float *t)
	{

	}

	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray)
	{

	}

	virtual VECTOR3D get_normal(VECTOR3D point)
	{
	}
};

	
#endif //__PLANE_H__

