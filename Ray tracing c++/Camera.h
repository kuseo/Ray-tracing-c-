#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "VECTOR3D.h"

class Camera
{
public:
	/*
	member variables
	*/
	VECTOR3D eye;
	VECTOR3D center;
	VECTOR3D up;
	VECTOR3D right;
	float fov;

	/*
	constructor
	*/
	Camera() : eye(0.0, 0.0, 0.0), center(0.0, 0.0, -1.0) { up = VECTOR3D(0.0, 1.0, 0.0); right = VECTOR3D(1.0, 0.0, 0.0); }

	/*
	destructor
	*/
	~Camera() {}

	/*
	member function
	*/

	/*
	setter
	*/

	/*
	getter
	*/
};

#endif //__CAMERA_H__