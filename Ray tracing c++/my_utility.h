#ifndef __MY_UTILITY_H__
#define __MY_UTILITY_H__

#include <stdlib.h>
#include <time.h>
#include "VECTOR3D.h"

VECTOR3D randomVector()
{
	VECTOR3D output;

	output.x = (rand() % 60) / 100.0f;

	output.y = (rand() % 60) / 100.0f;

	output.z = (rand() % 60) / 100.0f;

	return output;
}

void printVector(VECTOR3D v)
{
	printf("(%lf, %lf, %lf)\n", v.x, v.y, v.z);
}

#endif //__MY_UTILITY_H__