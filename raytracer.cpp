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

    glBegin( GL_POINTS );
    for( int y = 0; y < WINDOW_HEIGHT; y++ ){
        for( int x = 0; x < WINDOW_WIDTH; x++ ){

            model_space( Point3( 250, 250, -550 ), Point3( x, y, 0 ) );
            
            glVertex2d( x, y );
        }

        cout << y << endl;
    }
    glEnd();

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

