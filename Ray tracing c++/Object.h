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
	virtual VECTOR3D get_normal(VECTOR3D point) = 0 {}
	virtual VECTOR3D get_normal() = 0 {}
	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray)
	{
		/*
			normal vector
			*/
		VECTOR3D N = get_normal(point);
		N.Normalize();

		/*
		ray vector
		*/
		VECTOR3D I = ray - point;
		I.Normalize();

		/*
		light vector
		*/
		VECTOR3D L = light - point;
		L.Normalize();

		/*
		reflection vector
		*/
		VECTOR3D R = (L * -1.0) + N * 2.0 * L.InnerProduct(N);

		float diffuse = fmaxf(0.0f, N.InnerProduct(L));
		float specular = pow(fmaxf(0.0f, I.InnerProduct(R)), k_shineness);


		return k_diffuse * diffuse + k_specular * specular;
	}

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