/***
 * Sphere
 * An object for calculating sphere information and intersection
 * Also converts coordinates from previous set-up to current set-up.
 ***/
#ifndef SPHERE_H
#define SPHERE_H


#include "stdafx.h"
#include "../vecmath.h"
#include "gl/glut.h"
#include "Light.h"
using namespace std;

class Sphere {
	public:

	float _x, _y, _z, _r; // Coordinates of the center of the sphere, and radius
	// Light Controls
	Light l_ambient;
	Light l_diffuse;
	Light l_specular;
	float l_exponent;

	float _red;
	float _green;
	float _blue;

	// Constructor for defaults ( No light functions )
	Sphere( float, float, float, float);
	// Constructor for adding light components
	Sphere( float, float, float, float, Light, Light, Light, float );
	
	void setLighting( Light ambient, Light diffuse, Light specular, float exponent );
	void setColors( float red, float green, float blue );

	bool intersect( Point3, Vector3 );
	void phong_ambientlight();
};
#endif