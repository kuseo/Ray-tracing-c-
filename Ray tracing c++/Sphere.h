#ifndef SPEHERE_H
#define SPEHERE_H

#include "Object.h"

class Sphere : public Object
{
public:
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


};

#endif