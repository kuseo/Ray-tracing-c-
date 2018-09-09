#ifndef __MY_UTILITY_H__
#define __MY_UTILITY_H__

#include <stdio.h>
#include "VECTOR3D.h"
#include "Matrix.h"

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

VECTOR3D MatrixToVector(const Matrix& source)
{
	VECTOR3D result;
	result.x = source.m[0];
	result.y = source.m[1];
	result.z = source.m[2];

	return result;
}

Matrix VectorToMatrix(const VECTOR3D& source, int Homogeneous)
{
	Matrix result;
	float temp[4] = { source.x, source.y, source.z, Homogeneous };
	result.setValue(temp, 4, 1);

	return result;
}

#endif //__MY_UTILITY_H__