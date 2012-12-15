// model.h -- Header file for the model
//

#include "stdafx.h"
#include <cstdlib>
#include <vector>
#include <gl/glut.h>
#include "..\vecmath.h"
#include "math.h"

/*** 
 * Coordinates and details for the mirror sphere
 ***/
bool mirror_sphere( Vector3, Vector3 );

/***
 * Coordinates and details for the glass sphere
 ***/
bool glass_sphere( Vector3, Vector3 );

/*** 
 * Coordinates and details for the floor.
 ***/
void floor( void );

/*** 
 * Position and place everything into model space.
 ***/
void model_space( Vector3, Vector3 );