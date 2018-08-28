/*
Ray tracing
*/
#include <stdio.h>
#include "Sphere.h"
#include "gl_helper.h"



GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  /* White diffuse light. */
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */

GLfloat s_position[][3] = { { 3.0, 2.0, 0.0 },		/* shpere 1 */
							{ -3.0, 2.0, 0.0 } };	/* shpere 2 */


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glutSwapBuffers();
}

void init(void)
{
	/* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 80.0,
		/* aspect ratio */ 1.0,
		/* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 5.0, 5.0,  /* eye is at (0,5,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, -1.0);      /* up vector */
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Ray  tracing");
	init();

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}