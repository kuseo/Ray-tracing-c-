#ifndef SPEHERE_H
#define SPEHERE_H

#include "Object.h"

class Sphere : public Object
{
public:

	/*
	member variables
	*/
	VECTOR3D cen;
	float rad;

	VECTOR3D k_ambient;
	VECTOR3D k_diffuse;
	VECTOR3D k_specular;
	float k_shineness;

	/*
	constructor
	*/
	Sphere() {}
	Sphere(VECTOR3D cen, float rad) :cen(cen), rad(rad) { }

	/*
	destructor
	*/
	~Sphere() {}

	/*
	member function
	*/
	virtual bool hit(Ray r, float *t)
	{}

	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray)
	{}

	virtual VECTOR3D get_normal(VECTOR3D point)
	{}

};

#endif