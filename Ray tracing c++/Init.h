#ifndef __INIT_H__
#define __INIT_H__

#include "gl_helper.h"
#define DIM 500

void Initialize(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(DIM, DIM);
	glutCreateWindow("Ray Tracing");
}

#endif //__INIT_H__