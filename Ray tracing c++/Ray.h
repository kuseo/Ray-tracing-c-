#ifndef RAY_H
#define RAY_H

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
};

#endif