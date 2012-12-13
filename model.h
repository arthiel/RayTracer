// model.h -- Header file for the model
//

#include "stdafx.h"
#include <cstdlib>
#include <vector>
#include <gl/glut.h>

/*** 
 * Coordinates and details for the mirror sphere
 ***/
GLfloat* mirror_sphere( float x, float y, float z );

/***
 * Coordinates and details for the glass sphere
 ***/
void glass_sphere( void );

/*** 
 * Coordinates and details for the floor.
 ***/
void floor( void );

/*** 
 * Position and place everything into model space.
 ***/
void model_space( void );