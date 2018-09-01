#ifndef __INIT_H__
#define __INIT_H__

#include "gl_helper.h"
#define DIM 800

void Initialize(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(DIM, DIM);
	glutCreateWindow("Ray Tracing");

	glEnable(GL_DEPTH_TEST);
}

#endif //__INIT_H__