#pragma once

#ifndef __GL_HELPER_H__
#define __GL_HELPER_H__

/*
On 64-bit Windows, we need to prevent GLUT from automatically linking against
glut32. We do this by defining GLUT_NO_LIB_PRAGMA. This means that we need to
manually add opengl32.lib and glut64.lib back to the link using pragmas.
Alternatively, this could be done on the compilation/link command-line, but
we chose this so that compilation is identical between 32- and 64-bit Windows.
*/
#ifdef _WIN64
#define GLUT_NO_LIB_PRAGMA
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OPENGL32.lib")
#pragma comment (lib, "Glu32.lib")
#pragma comment (lib, "glut64.lib")
#endif //_WIN64


#ifdef _WIN32
#include <GL/glew.h>
#include <GL/glut.h>


#define GET_PROC_ADDRESS( str ) wglGetProcAddress( str )

#endif //_WIN32


#endif //__GL_HELPER_H__
