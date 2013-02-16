// raytracer.cpp : The entry for the ray tracer
//

#include "stdafx.h"
#include <cstdlib>
#include <GL/glut.h>
#include "model.h"
#include "..\vecmath.h"
#include "Point.h"

using namespace std;

const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 500;

Point pixels[WINDOW_HEIGHT][WINDOW_WIDTH];

float lume = 0;
float l_max = 100;    // Luminance Max [0...1]
float ld_max = 100; // Device Max 100 nits.

/** 
 * Ward Tone Reproduction
 **/
void ward_tone(){
        // Ward Luminance
   float log_avg_lum = 0;

    for( int x = 0; x < WINDOW_HEIGHT; x++ ){
        for( int y = 0; y < WINDOW_WIDTH; y++ ){
            log_avg_lum += log ( .001 + pixels[y][x].luminance );
        }
    }
    log_avg_lum = exp( (1 / (WINDOW_HEIGHT * WINDOW_WIDTH )) * log_avg_lum);
           // glVertex2d( x, y );
    float m = ( 1 / ld_max ) * pow(( ( 1.219 + pow((ld_max/2), 0.4)) / 1.219 + pow( log_avg_lum, 0.4 ) ), 2.5 );

    glBegin( GL_POINTS );
    for( int x = 0; x < WINDOW_HEIGHT; x++ ){
        for( int y = 0; y < WINDOW_WIDTH; y++ ){    
            pixels[y][x].l_red = (pixels[y][x].l_red * m) / ld_max;
            pixels[y][x].l_green = (pixels[y][x].l_green * m) / ld_max ;
            pixels[y][x].l_blue = (pixels[y][x].l_blue * m) / ld_max;

            glColor3f( pixels[y][x].l_red, pixels[y][x].l_green, pixels[y][x].l_blue );
            glVertex2d( x, y );
        }
    }
    glEnd();
}

/**
 * Reinhard Tone Reproduction 
 **/

/***
* Sets up the display.
***/
void display( void ){
    glClearColor( 0, 0, 1, 0 );
    glClear( GL_COLOR_BUFFER_BIT );

    //Point pixels[WINDOW_HEIGHT][WINDOW_WIDTH];

    //glBegin( GL_POINTS );
    for( int y = 0; y < WINDOW_HEIGHT; y++ ){
        for( int x = 0; x < WINDOW_WIDTH; x++ ){

            pixels[y][x] = model_space( Point3( 250, 250, -550 ), Point3( x, y, 0 ) );
            glColor3f( pixels[y][x].l_red, pixels[y][x].l_green, pixels[y][x].l_blue );

            // Multiply each pixel by max luminance.
            pixels[y][x].l_red = l_max * pixels[y][x].l_red;
            pixels[y][x].l_green = l_max * pixels[y][x].l_green;
            pixels[y][x].l_blue = l_max * pixels[y][x].l_blue;

            pixels[y][x].setLuminance();
        }
        //cout << y << endl;
    }
    //glEnd();

    //ward_tone();


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

