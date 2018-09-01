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
	virtual void setAmbient(VECTOR3D v) { k_ambient = v; }
	virtual void setDiffuse(VECTOR3D v) { k_diffuse = v; }
	virtual void setSpecular(VECTOR3D v) { k_specular = v; }
	virtual void setShineness(float value) { k_shineness = value; }

	/*
	getter
	*/
	virtual VECTOR3D getAmbient() { return k_ambient; }
	virtual VECTOR3D getDiffuse() { return k_diffuse; }
	virtual VECTOR3D getSpecular() { return k_specular; }
};

#endif //__OBJECT_H__