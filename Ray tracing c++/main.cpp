/*************************
*	Ray Tracing			 *
*	08.29.18			 *
*************************/

#include <stdio.h>
#include <vector>
#include "my_utility.h"
#include "Sphere.h"
#include "gl_helper.h"
#define DIM 800


using namespace std;

/*
get matrices
*/
GLdouble modelMatrix[16];
GLdouble projMatrix[16];
GLint viewport[4];

vector<Object*> objects;
vector<VECTOR3D> center;
VECTOR3D eye = VECTOR3D(0.0, 0.0, 0.0);			//position of the camera, which is the origin of the ray
VECTOR3D light = VECTOR3D(0.0, 1.0, 0.0);		//position of the light

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
	/*
	draw
	*/
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glBegin(GL_POINTS);
	for (int i = 0; i < glutGet(GLUT_WINDOW_WIDTH); i++)
		for (int j = 0; j < glutGet(GLUT_WINDOW_HEIGHT); j++)
		{
			/*
			ray casting
			*/
			double nearX, nearY, nearZ;

			if (gluUnProject(i, j, 0, modelMatrix, projMatrix, viewport, &nearX, &nearY, &nearZ) == GLU_FALSE)
			{
				printf("gluUnProject fail\n");
				printf("%d, %d\n", i, j);
				exit(0);
			}
			
			/*
			create ray
			*/
			VECTOR3D near((float)nearX, (float)nearY, (float)nearZ);
			VECTOR3D v = near - eye;
			v.Normalize();

			Ray ray(eye, v);

			/*
			finally, we call the raytrace function
			*/
			VECTOR3D color = raytrace(ray, 0);

			glColor3f(color.x, color.y, color.z);
			glVertex3f(near.x, near.y, near.z);
		}

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (h == 0)
		gluPerspective(80, (float)w, 1.0, 5000.0);
	else
		gluPerspective(80, (float)w / (float)h, 1.0, 5000.0);

	glMatrixMode(GL_MODELVIEW);

	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
}


void key(unsigned char key, int x, int y)
{
	/*
	ESC Ű�� ���ø����̼� ����
	*/
	switch (key)
	{
	case '27':
		exit(0);
	case ' ':
		printf("press space bar\n");
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(DIM, DIM);
	glutCreateWindow("Ray Tracing");

	objects.resize(3);
	center.resize(3);
	center[0] = VECTOR3D(2.0, 2.0, -8.0);
	center[1] = VECTOR3D(-2.0, 2.0, -8.0);
	center[2] = VECTOR3D(0.0, 2.0, -10.0);

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i] = new Sphere(center[i], 2.0);
	}
	

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}