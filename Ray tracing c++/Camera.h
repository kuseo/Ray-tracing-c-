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
	float fov;

	/*
	constructor
	*/
	Camera() : pos(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f), speed(2.0f) { }

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