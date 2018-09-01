#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <stdlib.h>
#include <time.h>
#include "VECTOR3D.h"

void randomVector(VECTOR3D *v)
{
	VECTOR3D output;

	v->x = (rand() % 60) / 100.0f;

	v->y = (rand() % 60) / 100.0f;

	v->z = (rand() % 60) / 100.0f;

	return;
}

void printVector(VECTOR3D v)
{
	printf("(%lf, %lf, %lf)\n", v.x, v.y, v.z);
}

void calculateUp(VECTOR3D input, VECTOR3D *output)
{

}

#endif