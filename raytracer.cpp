// raytracer.cpp : The entry for the ray tracer
//

#include "stdafx.h"
#include <cstdlib>
#include <GL/glut.h>

using namespace std;

int WINDOW_HEIGHT = 500;
int WINDOW_WIDTH = 500;

/***
 * Sets up the display.
 ***/
void display( void ){
	glClearColor( 0, 0, 1, 0 );
	glClear( GL_COLOR_BUFFER_BIT );

	glFlush();
}

/***
 * GLUT Setup and such.
 ***/
int main(int argc, char* argv[])
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
	glutInitWindowSize( WINDOW_HEIGHT, WINDOW_WIDTH );
	glutCreateWindow( argv[0] );

	gluOrtho2D( 0, WINDOW_WIDTH, 0, WINDOW_HEIGHT );
	glutDisplayFunc( display );
	glutMainLoop();

	return 0;
}

