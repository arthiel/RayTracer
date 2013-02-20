/***
 * Light
 * An object for calculating Light information.
 * Also converts coordinates from previous set-up to current set-up.
 * Author: Emily Egeland
 * Computer Graphics II Winter 20122
 ***/
#ifndef LIGHT_H
#define LIGHT_H

#include "stdafx.h"
#include "../vecmath.h"

using namespace std;

class Light {
	public:

	float _red;
	float _green;
	float _blue;
	float _ammount;
	Point3 _position;

	Light();
	// Constructor for defaults ( No light functions )
	Light( float, float, float, float);
	Light( float, float, float, float, Point3 );
};
#endif