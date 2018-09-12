/*************************
*	Ray Tracing			 *
*	08.29.18			 *
*************************/

/*
	To Do :
	polygon, plane, mesh loader, refraction
*/
#pragma warning(disable:4996)

#include <stdio.h>
#include <vector>
#include "my_utility.h"
#include "Sphere.h"
#include "Plane.h"
#include "Polygon.h"
#include "Camera.h"
#include "Init.h"

#undef near
#undef far

using namespace std;

int depth = 0;

/*
openGL view matrix
*/
GLdouble modelMatrix[16];
GLdouble projMatrix[16];
GLint viewport[4];

vector<Object*> objects;		//obejets
VECTOR3D light = VECTOR3D(0.0f, 10.0f, -8.0f);		//position of the light
Camera canon;		//Camera
vector<Object*> Buffer;		//buffer objects

const VECTOR3D eye = VECTOR3D(0.0f, 0.0f, 0.0f);			//origin of the ray in world space
float deltaTime = 0.0f;		//time between current and last frame
float lastTime = 0.0f;		//time of last frame

VECTOR3D raytrace(Ray ray, int depth)
{
	/*
	infinite distance
	*/
	float min_t = 10000.0f;

	Object *o = NULL;

	/*
	find the first object that collides with ray
	*/
	for (int i = 0; i < Buffer.size(); i++)
	{
		float t;
		Object *obj = Buffer[i];

		if (obj->hit(ray, &t))
		{
			if (t <= min_t)
			{
				min_t = t;
				o = obj;
			}
		}
	}

	if (min_t == 10000.0f)
		return VECTOR3D(0.4, 0.4, 0.4);		//background color

	float shadow = 1.0f;
	float min_st = 10000.0f;

	/*
	point where ray and object are intersected
	*/
	VECTOR3D point = ray.position(min_t);

	/* light vector */
	VECTOR3D L = light - point;
	L.Normalize();

	Ray shadow_ray(point, L);

	for (int i = 0; i < Buffer.size(); i++)
	{
		float t;
		Object *obj = Buffer[i];

		if (obj->hit(shadow_ray, &t))
			if (t <= min_st)
				min_st = t;
	}

	if (min_st == 10000.0f)
		shadow = 1.0f;
	else
		shadow = 0.5f;

	/*
	normal vector at the surface of the object
	*/
	VECTOR3D N = o->get_normal(point);
	N.Normalize();

	/*
	reflection vector
	*/
	VECTOR3D Reflection = (L * -1.0f) + N * 2.0f * ((L.InnerProduct(N)));
	
	if (depth > 0)
		return o->k_ambient + (o->getColor(point, light, ray.origin)) * shadow
			+ raytrace(Ray(point, Reflection), depth - 1) * 0.3f
			+ raytrace(Ray(point, ray.dir), depth - 1) * 0.1f;
		
	else
		return o->k_ambient + o->getColor(point, light, ray.origin) * shadow;
}

void myLookAt(Camera camera)
{
	/*
	calculate LookAt matrix
	*/
	camera.right.Normalize();
	camera.up.Normalize();
	camera.dir.Normalize();
	float RUD[16] =
	{
		camera.right.x, camera.right.y, camera.right.z, 0.0f,
		camera.up.x, camera.up.y, camera.up.z, 0.0f,
		camera.dir.x, camera.dir.y, camera.dir.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	float P[16] =
	{
		1.0f, 0.0f, 0.0f, -camera.pos.x,
		0.0f, 1.0f, 0.0f, -camera.pos.y,
		0.0f, 0.0f, 1.0f, -camera.pos.z,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	Matrix _RUD, _P, LookAt;
	_RUD.setValue(RUD, 4, 4);
	_P.setValue(P, 4, 4);
	LookAt = _RUD * _P;

	/*
	transform all objects and lights to camera world
	*/
	for (int i = 0; i < Buffer.size(); i++)
		Buffer[i]->matrixMult(LookAt);

	Matrix m_light = VectorToMatrix(light, 1.0f);
	m_light = LookAt * m_light;
	light = MatrixToVector(m_light);
}

void display(void)
{
	/*
	clear buffer
	*/
	for (int i = 0; i < Buffer.size(); i++)
		delete(Buffer[i]);
	Buffer.clear();

	/*
	copy objects to Buffer
	*/
	Buffer.resize(objects.size());
	for (int i = 0; i < objects.size(); i++)
	{
		switch (objects[i]->getClassType())
		{
		case PLANE:
			Buffer[i] = new Plane();
			break;
		case POLYGON:
			Buffer[i] = new Polygon();
			break;
		case SPHERE:
			Buffer[i] = new Sphere();
			break;
		}
		Buffer[i] = objects[i]->clone();
		*Buffer[i] = *objects[i];
	}

	/*
	draw
	*/
	myLookAt(canon);

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int i = 0; i < glutGet(GLUT_WINDOW_WIDTH); i++)
		for (int j = 1; j <= glutGet(GLUT_WINDOW_HEIGHT); j++)
		{
			/*
			ray casting
			*/
			double nearX, nearY, nearZ;

			if (gluUnProject(i, glutGet(GLUT_WINDOW_HEIGHT)- j, 0, modelMatrix, projMatrix, viewport, &nearX, &nearY, &nearZ) == GLU_FALSE)
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
			VECTOR3D color = raytrace(ray, depth);

			glColor3f(color.x, color.y, color.z);
			glVertex3f(near.x, near.y, near.z);
		}

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	GLdouble wfactor = (GLdouble)w / (GLdouble)DIM;
	GLdouble hfactor = (GLdouble)h / (GLdouble)DIM;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * wfactor, 1.0 * wfactor, -1.0 * hfactor, 1.0 * hfactor, -1.0, 1.0);

	/*
	get matrices
	*/
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);

	glutPostRedisplay();
}


void key(unsigned char key, int x, int y)
{
	/*
	ESC Ű�� ���ø����̼� ����
	*/
	switch (key)
	{
	case 27:
		exit(0);
	case 'w':
	case 'W':
		canon.pos.y += 0.1f;
		break;
	case 'a':
	case 'A':
		canon.pos.x -= 0.1f;
		break;
	case 's':
	case 'S':
		canon.pos.y -= 0.1f;
		break;
	case 'd':
	case 'D':
		canon.pos.x += 0.1f;
		break;
	}

	glutPostRedisplay();
}

void arrowkey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	printf("depth : ");
	scanf("%d", &depth);

	srand(99);
	
	Initialize(argc, argv);
	
	/**********************
	Load or Create objects
	**********************/
	vector<VECTOR3D> center;
	center.resize(3);
	center[0] = VECTOR3D(2.0, -2.0, -8.0);
	center[1] = VECTOR3D(-2.0, -2.0, -8.0);
	center[2] = VECTOR3D(0.0, -2.0, -11.0);
	/*
	create three balls.
	*/
	int index = 0;
	while (true)
	{
		objects.push_back(new Sphere(center[index], 2.0));
		objects[objects.size() - 1]->setAmbient(randomVector());
		objects[objects.size() - 1]->setDiffuse(randomVector());
		objects[objects.size() - 1]->setSpecular(randomVector());
		objects[objects.size() - 1]->setShineness(32.0);
		index++;

		if (index == 3)
			break;
	}

	/*
	create infinite plane
	*/
	VECTOR3D plane_normal = VECTOR3D(0.0, 1.0, 0.0);
	VECTOR3D plane_dot = VECTOR3D(0.0, -5.0, 0.0);
	VECTOR3D temp = VECTOR3D(0.3, 0.3, 0.3);
	objects.push_back(new Plane(plane_normal, plane_dot));
	objects[objects.size() - 1]->setAmbient(temp);
	objects[objects.size() - 1]->setDiffuse(temp);
	objects[objects.size() - 1]->setSpecular(temp);
	objects[objects.size() - 1]->setShineness(1.0);

	/*
	create a polygon
	*/
	temp = VECTOR3D(2.0, 2.0, 2.0);
	for (int i = 0; i < 3; i++)
		center[i] += temp;
	objects.push_back(new Polygon(center[0], center[1], center[2]));
	objects[objects.size() - 1]->setAmbient(temp);
	objects[objects.size() - 1]->setDiffuse(temp);
	objects[objects.size() - 1]->setSpecular(temp);
	objects[objects.size() - 1]->setShineness(1.0);
	


	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutSpecialFunc(arrowkey);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}