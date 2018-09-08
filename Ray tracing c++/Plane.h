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

			/*
			we set this condition to avoid self collision when calculate reflection and refraction
			*/
			if (*t > 0.01f)
				return true;
			else
				return false;
				
		}
	}

	virtual VECTOR3D get_normal(VECTOR3D point) { return normal; }	//don't use
	virtual VECTOR3D get_normal() { return normal; }

	virtual void matrixMult(Matrix m)
	{
		/*
		make Homogeneous cooldinates
		*/
		float n[4] = { normal.x, normal.y, normal.z, 0.0f };
		float d[4] = { dot.x, dot.y, dot.z, 1.0f };

		Matrix m_normal, m_dot, temp;
		m_normal.setValue(n, 4, 1);
		m_dot.setValue(d, 4, 1);

		temp = m * m_normal;
		normal.x = temp.m[0];
		normal.y = temp.m[1];
		normal.z = temp.m[2];

		temp = m * m_dot;
		dot.x = temp.m[0];
		dot.y = temp.m[1];
		dot.z = temp.m[2];
	}

};

	
#endif //__PLANE_H__

