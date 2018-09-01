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
		float denom = r.dir.InnerProduct(normal);

		/*
		ray doesn't intersect with plane
		*/
		if (denom == 0.0f)
		{
			*t = 10000.0f;
			return false;
		}

		/*
		ray intersect with plane
		*/
		else
		{
			VECTOR3D temp = dot - r.origin;
			float numerator = temp.InnerProduct(normal);
			*t = numerator / denom;
			return true;
		}
	}

	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray)
	{
		/*
		normal vector
		*/
		VECTOR3D N = get_normal();
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

	virtual VECTOR3D get_normal(VECTOR3D point) { return normal; }
	virtual VECTOR3D get_normal() { return normal; }
};

	
#endif //__PLANE_H__

