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
	Polygon(VECTOR3D a, VECTOR3D b, VECTOR3D c) :
		a(a), b(b), c(c) {}

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

	virtual VECTOR3D get_normal(VECTOR3D point) { return VECTOR3D(0.0, 0.0, 0.0); }	//don't use

	virtual VECTOR3D get_normal()
	{
		VECTOR3D edgeAB = b - a;
		VECTOR3D edgeAC = c - a;
		return edgeAB.CrossProduct(edgeAC);
	}
};

#endif // __POLYGON_H__
