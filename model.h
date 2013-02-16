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

Point light_intersect( Point pixel, Point interGlass, Point interMirror, Light source[], Vector3 dir, Sphere glass );
bool intersect( Point pixel, Point inter );
Point cone_reflection( Sphere glass, Sphere mirror, Floor thisFloor, Point pixel, Vector3 refRay, int depth);
Point intersection(Sphere glass, Sphere mirror, Floor thisFloor, Point3 origin, Vector3 dir, int depth );
Point more_lightsource( Point pixel, Sphere glass, Sphere mirror );


/*** 
 * Position and place everything into model space.
 ***/
Point model_space( Point3, Point3 );

#endif