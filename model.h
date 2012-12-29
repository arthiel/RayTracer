// model.h -- Header file for the model
//
#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include <cstdlib>
#include <vector>
#include <gl/glut.h>
#include "..\vecmath.h"
#include "math.h"
#include "Light.h"
#include "Sphere.h"


/*** 
 * Coordinates and details for the floor.
 ***/
bool floor( Point3, Vector3 );

/*** 
 * Position and place everything into model space.
 ***/
void model_space( Point3, Point3 );

#endif 