#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "VECTOR3D.h"
#include <stdio.h>
#include <stdlib.h>

class Matrix
{
public:
	/*
	member variables
	*/
	float *m;
	int col, row;

	/*
	constructor
	*/
	Matrix() : col(0), row(0), m(0) {}

	/*
	destructor
	*/
	~Matrix() {}

	/*
	member function
	*/
	void setValue(float *value, int row, int col);
	Matrix operator*(const Matrix& a);
	Matrix operator=(const Matrix& a);
	void showMatrix();
};

#endif //__MATRIX_H__