#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <stdlib.h>
#include <time.h>
#include "VECTOR3D.h"

VECTOR3D randomVector()
{
	VECTOR3D output;

	output.x = (rand() % 60) / 100.0f;

	output.y = (rand() % 60) / 100.0f;

	output.z = (rand() % 60) / 100.0f;

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