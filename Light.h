/***
 * Light
 * An object for calculating Light information.
 * Also converts coordinates from previous set-up to current set-up.
 ***/
#ifndef LIGHT_H
#define LIGHT_H

#include "stdafx.h"

using namespace std;

class Light {
	public:

	float _red;
	float _green;
	float _blue;
	float _ammount;

	Light();
	// Constructor for defaults ( No light functions )
	Light( float, float, float, float);
};
#endif