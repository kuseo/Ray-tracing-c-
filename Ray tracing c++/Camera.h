#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "VECTOR3D.h"
enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

/*
defluat camera values
*/
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.0f;
const float SENSITIVITY = 0.1f;

class Camera
{
public:
	/*
	member variables
	*/
	/* cameara attributes */
	VECTOR3D pos;
	VECTOR3D up;
	VECTOR3D front;
	VECTOR3D right;
	VECTOR3D worldup;

	/* euler angles */
	float yaw;
	float pitch;

	/* camera options */
	float speed;
	float sensitivity;

	/*
	constructor
	*/
	Camera() :
		pos(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), front(0.0f, 0.0f, -1.0f),
		yaw(YAW), pitch(PITCH)
	{
		this->worldup = up;
		updateCameraVectors();
	}
	Camera(VECTOR3D pos,VECTOR3D up, float yaw, float pitch) :
		front(0.0f, 0.0f, -1.0f), 
		speed(SPEED), sensitivity(SENSITIVITY)
	{
		this->pos = pos;
		this->worldup = up;
		this->yaw = yaw;
		this->pitch = pitch;
		updateCameraVectors();
	}

	/*
	destructor
	*/
	~Camera() {}

	/*
	member function
	*/
	void updateCameraVectors()
	{
		VECTOR3D front;
		front.x = cos(radian(yaw)) * cos(radian(pitch));
		front.y = sin(radian(pitch));
		front.z = sin(radian(yaw)) * cos(radian(pitch));
		front.Normalize();
		right = front.CrossProduct(worldup);
		right.Normalize();
		up = right.CrossProduct(front);
		up.Normalize();
	}

	/*
	setter
	*/

	/*
	getter
	*/
};

#endif //__CAMERA_H__