#ifndef __RAY_H__
#define __RAY_H__

#include "VECTOR3D.h"

struct Ray
{
	VECTOR3D origin;
	VECTOR3D dir;

	Ray(VECTOR3D origin, VECTOR3D dir)
	{
		this->origin = origin;
		this->dir = dir;
	}

	VECTOR3D position(float t)
	{
		return origin + dir * t;
	}
};

#endif //__RAY_H__