/***
 * Sphere
 * An object for calculating sphere information and intersection
 * Also converts coordinates from previous set-up to current set-up.
 ***/
#ifndef SPHERE_H
#define SPHERE_H
#endif

#include "stdafx.h"
#include "model.h"
#include "../vecmath.h"
using namespace std;

class Sphere {
	float _x, _y, _z, _r; // Coordinates of the center of the sphere, and radius

public:
	Sphere( float, float, float, float);
	
	bool intersect( Point3, Vector3 );
};