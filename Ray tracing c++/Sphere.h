#ifndef __SPEHERE_H__
#define __SPEHERE_H__

#include "Object.h"

class Sphere : public Object
{
public:

	/*
	member variables
	*/
	VECTOR3D cen;
	float rad;

	/*
	constructor
	*/
	Sphere() {}
	Sphere(VECTOR3D cen, float rad) : cen(cen), rad(rad) { }

	/*
	destructor
	*/
	~Sphere() {}

	/*
	member function
	*/
	virtual bool hit(Ray r, float *t)
	{
		float b = 2.0f * r.dir.InnerProduct(r.origin - cen);
		float c = pow((r.origin - cen).Magnitude(), 2) - (rad * rad);
		float d = b * b - (4.0f * c); //discriminant

		/*
		ray doesn't intersect with sphere
		*/
		if (d < 0.0f)
		{
			*t = 10000.0;
			return false;
		}

		/*
		ray intersect at only one point
		*/
		else if (d == 0.0f)
		{
			*t = (-1.0f * b) / 2.0f;

			/*
			we set this condition to avoid self collision when calculate reflection and refraction
			*/
			if (*t > 0.01f)
				return true;
			else
				return false;
		}

		/*
		ray intersect at two points
		*/
		else
		{
			float t1 = ((-1.0f * b) - sqrt(d)) / 2.0f;
			float t2 = ((-1.0f * b) + sqrt(d)) / 2.0f;

			/*
			sphere shoud be at the positive direction of the ray 
			*/
			if (t1 > 0.01f && t2 > 0.01f)
			{
				*t = (t1 < t2) ? t1 : t2;
				return true;
			}
			else
				return false;
		}
	}

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
	
	virtual VECTOR3D get_normal(VECTOR3D point) { return point - cen; }
	virtual VECTOR3D get_normal() { return VECTOR3D(0.0, 0.0, 0.0); }	//don't use
};

#endif //__SPEHERE_H__