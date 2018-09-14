#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "VECTOR3D.h"

class Camera
{
public:
	/*
	member variables
	*/
	VECTOR3D pos;
	VECTOR3D dir;
	VECTOR3D up;
	VECTOR3D right;
	float speed;

	/*
	constructor
	*/
	Camera() : pos(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f), speed(2.0f) { }
	Camera(float px, float py, float pz, float dx, float dy, float dz, float ux, float uy, float uz) :
		pos(px, py, pz), dir(dx, dy, dz), up(ux, uy, uz)
	{
		right = dir.CrossProduct(up);
	}

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