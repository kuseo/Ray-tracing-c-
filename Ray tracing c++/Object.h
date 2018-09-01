#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Ray.h"

class Object
{
public:
	/*
	member variables
	*/
	VECTOR3D k_ambient;
	VECTOR3D k_diffuse;
	VECTOR3D k_specular;
	float k_shineness;

	/*
	constructor
	*/
	Object() {}

	/*
	destructor
	*/
	virtual ~Object() {}

	/*
	member function
	*/
	virtual bool hit(Ray r, float *t) = 0 {}
	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray) = 0 {}
	virtual VECTOR3D get_normal(VECTOR3D point) = 0 {}
	
	/*
	setter
	*/
	virtual void setAmbient(VECTOR3D v) = 0 {};
	virtual void setDiffuse(VECTOR3D v) = 0 {};
	virtual void setSpecular(VECTOR3D v) = 0 {};

	/*
	getter
	*/
	virtual VECTOR3D getAmbient() {};
	virtual VECTOR3D getDiffuse() {};
	virtual VECTOR3D getSpecular() {};
};

#endif //__OBJECT_H__