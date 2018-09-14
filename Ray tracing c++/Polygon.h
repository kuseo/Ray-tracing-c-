#ifndef __POLYGON_H__
#define __POLYGON_H__

#include "Object.h"
#include "Plane.h"

class Polygon : public Object
{
public:
	/*
	member variables
	*/
	VECTOR3D a, b, c;

	/*
		constructor
	*/
	Polygon() {}
	Polygon(VECTOR3D a, VECTOR3D b, VECTOR3D c) : a(a), b(b), c(c) {}
	Polygon(const Polygon& P) : a(P.a), b(P.b), c(P.c) {}

	/*
	destructor
	*/
	virtual ~Polygon() {}

	/*
	member function
	*/
	void varicentric(Ray r, float *alpha, float *beta, float *gamma)
	{
		VECTOR3D edgeAB = b - a;
		VECTOR3D edgeAC = c - a;
		VECTOR3D pvec = r.dir.CrossProduct(edgeAC);
		float det = edgeAB.InnerProduct(pvec);	//matrix determinant

		float invDet = 1 / det;	//inverse of determinant

		VECTOR3D tvec = r.origin - a;
		*beta = tvec.InnerProduct(pvec) * invDet;

		VECTOR3D qvec = tvec.CrossProduct(edgeAB);
		*gamma = r.dir.InnerProduct(qvec) * invDet;

		*alpha = 1 - *beta - *gamma;
	}

	virtual bool hit(Ray r, float *t)
	{
		float alpha, beta, gamma;
		this->varicentric(r, &alpha, &beta, &gamma);

		/*
		ray doesn't intersect with polygon
		*/
		if (alpha < 0 || alpha > 1 ||
			beta < 0 || beta > 1 ||
			gamma < 0 || gamma >1)
			return false;

		/*
		ray intersect with polygon
		*/
		else
		{
			/*
			create infinite plane that contains polygon to get the intersection point
			*/
			VECTOR3D edgeAB = b - a;
			VECTOR3D edgeAC = c - a;
			VECTOR3D n = edgeAB.CrossProduct(edgeAC);	//normal
			Plane polygon(n, this->a);

			return polygon.hit(r, t);
		}
	}

	virtual VECTOR3D get_normal(VECTOR3D point) 
	{ 
		VECTOR3D edgeAB = b - a;
		VECTOR3D edgeAC = c - a;
		return edgeAB.CrossProduct(edgeAC);
	}

	virtual void matrixMult(Matrix m)
	{
		/*
		make Homogeneous cooldinates
		*/
		Matrix m_a, m_b, m_c;
		m_a = VectorToMatrix(a, 1.0f);
		m_b = VectorToMatrix(b, 1.0f);
		m_c = VectorToMatrix(c, 1.0f);

		m_a = m * m_a;
		a = MatrixToVector(m_a);

		m_b = m * m_b;
		b = MatrixToVector(m_b);

		m_c = m * m_c;
		c = MatrixToVector(m_c);
	}

	virtual int getClassType() { return POLYGON; }

	virtual Polygon* doClone() const { return new Polygon(*this); }

	Polygon* clone() const { return doClone(); }
};

#endif // __POLYGON_H__
