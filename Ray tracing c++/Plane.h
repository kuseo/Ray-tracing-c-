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
		Matrix m_normal, m_dot, temp;
		m_normal = VectorToMatrix(normal, 0.0f);
		m_dot = VectorToMatrix(dot, 1.0f);

		m_normal = m * m_normal;
		normal = MatrixToVector(m_normal);

		m_dot = m * m_dot;
		dot = MatrixToVector(m_dot);
	}

};

	
#endif //__PLANE_H__

