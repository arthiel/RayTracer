// model.h -- Header file for the model
//
#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include <cstdlib>
#include <gl/glut.h>
#include "..\vecmath.h"
#include "math.h"
#include "Point.h"
#include "Light.h"
#include "Sphere.h"
#include "Floor.h"

// Phong Lighting on Model.
Point phong_ambientlight(Point dot, Light amb);
Point phong_diffuselight(Point dot, Light diffuse);
Point phong_speclight(Point dot, Light spec, float exponent);

/*** 
 * Position and place everything into model space.
 ***/
void model_space( Point3, Point3 );

#endif