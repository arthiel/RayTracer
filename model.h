// model.h -- Header file for the model
//

#include "stdafx.h"
#include <cstdlib>
#include <vector>
#include <gl/glut.h>
#include "..\vecmath.h"
#include "math.h"

/*** 
 * Coordinates and details for the floor.
 ***/
bool floor( Point3, Vector3 );

/*** 
 * Position and place everything into model space.
 ***/
void model_space( Point3, Point3 );