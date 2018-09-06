#ifndef __POLYGON_H__
#define __POLYGON_H__

#include "Object.h"
class Polygon : public Object
{
public:
	/*
	member variables
	*/
	VECTOR3D a, b, c;
	float alpha, beta, gamma;

	/*
		constructor
	*/
	Polygon() {}
	Polygon(VECTOR3D a, VECTOR3D b, VECTOR3D c) :
		a(a), b(b), c(c) {}

	/*
	destructor
	*/
	virtual ~Polygon() {}

	/*
	member function
	*/
	void varicentric(Ray r)
	{
		VECTOR3D edgeAB = b - a;
		VECTOR3D edgeAC = c - a;
		VECTOR3D pvec = r.dir.CrossProduct(edgeAC);
		float det = edgeAB.InnerProduct(pvec);	//matrix determinant

		float invDet = 1 / det;	//inverse of determinant

		VECTOR3D tvec = r.origin - a;
		this->beta = tvec.InnerProduct(pvec) * invDet;

		VECTOR3D qvec = tvec.CrossProduct(edgeAB);
		gamma = r.dir.InnerProduct(qvec) * invDet;

		alpha = 1 - beta - gamma;
	}

	virtual bool hit(Ray r, float *t)
	{

	}

	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray)
	{

	}

	virtual VECTOR3D get_normal(VECTOR3D point)
	{

	}

	virtual VECTOR3D get_normal()
	{

	}
};

#endif // __POLYGON_H__
