// raytracer.cpp : The entry for the ray tracer
//

#include "stdafx.h"
#include <cstdlib>
#include <GL/glut.h>
#include "model.h"
#include "..\vecmath.h"

using namespace std;

int WINDOW_HEIGHT = 500;
int WINDOW_WIDTH = 500;

/***
 * Sets up the display.
 ***/
void display( void ){
	glClearColor( 0, 0, 1, 0 );
	glClear( GL_COLOR_BUFFER_BIT );


	for( int y = 0; y < WINDOW_HEIGHT; y++ ){
		for( int x = 0; x < WINDOW_WIDTH; x++ ){
		//	model_space( Vector3( 80, 0, 120 ), Vector3( x, y, 0 ) );
			model_space( Vector3( 250, 250, -550 ), Vector3( x, y, 0 ) );
			//glColor3f( 1, 0, 0 );
			glBegin( GL_POINTS );
				glVertex2d( x, y );
			glEnd();
		}
						cout << y << endl;

	}

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

