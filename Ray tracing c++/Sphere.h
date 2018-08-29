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
	float k_shineness = 0.6;

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
	{
		float b = 2.0 * r.dir.InnerProduct(r.origin - cen);
		float c = pow((r.origin - cen).Magnitude(), 2) - (rad * rad);
		float d = b * b - (4.0 * c); //discriminant

		/*
		ray doesn't intersect with sphere
		*/
		if (d < 0.0)
		{
			*t = 10000.0;
			return false;
		}

		/*
		ray intersect at only one point
		*/
		else if (d == 0.0)
		{
			*t = (-1.0 * b) / 2.0;

			/*
			we set this condition to avoid self collision when calculate reflection and refraction
			*/
			if (*t > 0.01)
				return true;
			else
				return false;
		}

		/*
		ray intersect at two points
		*/
		else
		{
			float t1 = ((-1.0 * b) - sqrt(d)) / 2.0;
			float t2 = ((-1.0 * b) + sqrt(d)) / 2.0;

			/*
			sphere shoud be at the positive direction of the ray 
			*/
			if (t1 > 0.01 && t2 > 0.01)
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

		/*
		ÀÔ»ç±¤ º¤ÅÍ
		*/
		VECTOR3D L = light - point;
		L.Normalize();

		/*
		¹Ý»ç±¤ º¤ÅÍ
		*/
		VECTOR3D R = (L * -1.0) + N * 2.0 * ((L.InnerProduct(N)));

		float diffuse = fmaxf(0.0, N.InnerProduct(L));
		float specular = pow(fmaxf(0.0, I.InnerProduct(R)), k_shineness);

		return  k_diffuse * diffuse + k_specular * specular;
	}

	virtual VECTOR3D get_normal(VECTOR3D point)
	{
		return point - cen;
	}

};

#endif