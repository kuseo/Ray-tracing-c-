#include "Matrix.h"

void Matrix::setValue(float * value, int col, int row)
{
	this->col = col;
	this->row = row;

	if (this->m)
		delete(this->m);

	this->m = new float(col * row);

	for (int i = 0; i < col * row; i++)
		this->m[i] = value[i];
}

Matrix Matrix::operator*(const Matrix & a)
{
	if (this->col != a.row)
	{
		printf("Matrix dimension error (operator*)\n");
		exit(0);
	}

	float *temp = new float(this->row * a.col);
	for (int i = 0; i < this->row * a.col; i++)
		temp[i] = 0.0f;

	for (int i = 0; i < this->row; i++)
		for (int j = 0; j < a.col; j++)
			for (int k = 0; k < this->col; k++)
				temp[i*a.col + j] += this->m[i * this->col + k] * a.m[k * a.col + j];

	Matrix output;
	output.setValue(temp, this->col, a.row);

	return output;
}

Matrix Matrix::operator=(const Matrix & a)
{	
	this->col = a.col;
	this->row = a.row;

	if (this->m)
		delete(m);

	this->m = new float(a.col * a.row);
	for (int i = 0; i < a.col * a.row; i++)
		this->m[i] = a.m[i];

	return *this;
}

void Matrix::showMatrix()
{
	for (int i = 0; i <= col * row; i++)
	{
		printf("%lf ", this->m[i]);
		if ((i + 1) % row == 0)
			printf("\n");
	}
}
