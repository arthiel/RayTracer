// model.cpp - The coordinates and model-space of the scene
// 
#include "stdafx.h"
#include "model.h"
#include "Sphere.h"


/*** 
 * Coordinates and details for the floor.
 ***/
void floor( void ){
	// X1 : 10 , X2: 100
	// Y1 : -20 , Y2: -20
	// Z1 : -100 , Z2 : 200
}

/*** 
 * Position and place everything into model space.
 ***/
void model_space( Point3 origin, Point3 distance ){
	//glass_sphere();
	Vector3 dir = distance - origin;

	// Define world objects.
	Sphere glass( 0, .7, -235, 8 );
	Sphere mirror( -120, -5, -140, 8 );
	
	// Check if intersects glass, mirror, etc.
	if( glass.intersect( origin, dir ) ){ 
		glColor3f( 0, 1, 0 );
		return;
	}
	else if( mirror.intersect(origin, dir )){ 
		glColor3f( 1, 0, 0 );
		return;
	}

	else {
		glColor3f( 0, 0, 0 );
	}

	//floor();
}