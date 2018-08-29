/*
Ray tracing
*/
#include <stdio.h>
#include "Sphere.h"
#include "gl_helper.h"
#define DIM 800

using namespace std;

vector<Object*> objects;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

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