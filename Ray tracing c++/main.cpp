/*************************
*	Ray Tracing			 *
*	08.29.18			 *
*************************/

#include <stdio.h>
#include <vector>
#include "Sphere.h"
#include "gl_helper.h"
#define DIM 800

using namespace std;

GLdouble mvMatrix[16];
GLdouble projMatrix[16];
GLint viewport[4];

vector<Object*> objects;
vector<VECTOR3D> center;
VECTOR3D eye = VECTOR3D(0.0, 5.0, 5.0);			//position of the camera, which is the origin of the ray
VECTOR3D light = VECTOR3D(0.0, 10.0, 0.0);		//position of the light

VECTOR3D raytrace(Ray ray, int depth)
{
	/*
	infinite distance
	*/
	float min_t = 10000;

	Object *o = NULL;

	/*
	find the first object that collides with ray
	*/
	for (int i = 0; i < objects.size(); i++)
	{
		float t;
		Object *obj = objects[i];

		if (obj->hit(ray, &t))
		{
			if (t <= min_t)
			{
				min_t = t;
				o = obj;
			}
		}
	}

	if (min_t == 10000)
		return VECTOR3D(0.4, 0.4, 0.4);		//background color

	float shadow = 1.0;
	float min_st = 10000;

	/*
	point where ray and object are intersected
	*/
	VECTOR3D point = ray.position(min_t);

	/* light vector */
	VECTOR3D L = light - point;
	L.Normalize();

	Ray shadow_ray(point, L);

	for (int i = 0; i < objects.size(); i++)
	{
		float t;
		Object *obj = objects[i];

		if (obj->hit(shadow_ray, &t))
			if (t <= min_st)
				min_st = t;
	}

	if (min_st = 10000)
		shadow = 1.0;
	else
		shadow = 0.5;

	/*
	normal vector at the surface of the object
	*/
	VECTOR3D N = o->get_normal(point);
	N.Normalize();

	/*
	reflection vector
	*/
	VECTOR3D Reflection = (L * -1.0) + N * 2.0 * ((L.InnerProduct(N)));

	if (depth > 0)
		return o->k_ambient + (o->getColor(point, light, ray.origin)) * shadow
		+ raytrace(Ray(point, Reflection), depth - 1) * 0.3;
		//+ raytrace(Ray(point, Refraction), depth - 1) * 0.3;
	else
		return o->k_ambient + o->getColor(point, light, ray.origin) * shadow;
}

void display(void)
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	Ray casting
	*/
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);

	glBegin(GL_POINTS);
	for (int i = 0; i < glutGet(GLUT_WINDOW_WIDTH); i++)
		for (int j = 0; j < glutGet(GLUT_WINDOW_HEIGHT); j++)
		{
			double nearX, nearY, nearZ;

			gluUnProject(i, j, 0, mvMatrix, projMatrix, viewport, &nearX, &nearY, &nearZ);
			
			VECTOR3D near((float)nearX, (float)nearY, (float)nearZ);

			Ray ray(eye, near - eye);

			VECTOR3D color = raytrace(ray, 0);

			glColor3f(color.x, color.y, color.z);

			glVertex3f(near.x, near.y, near.z);
		}

	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (height == 0)
		gluPerspective(80, (float)width, 1.0, 5000.0);
	else
		gluPerspective(80, (float)width / (float)height, 1.0, 5000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void key(unsigned char key, int x, int y)
{
	/*
	ESC 키로 어플리케이션 종료
	*/
	switch (key)
	{
	case '27':
		exit(0);
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(DIM, DIM);
	glutCreateWindow("Ray Tracing");

	objects.resize(3);
	center.resize(3);
	
	center[0] = VECTOR3D(2.0, 2.0, 2.0);
	center[1] = VECTOR3D(-2.0, 2.0, 2.0);
	center[2] = VECTOR3D(0.0, 2.0, -2.0);


	for (int i = 0; i < objects.size(); i++)
	{
		objects[i] = new Sphere(center[i], 2.0);
	}

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}