/*
Ray tracing
*/
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
VECTOR3D light = VECTOR3D(0.0, 0.0, 0.0);		//position of the light

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
	
	glutSwapBuffers();
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


	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}