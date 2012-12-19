// model.cpp - The coordinates and model-space of the scene
// 
#include "stdafx.h"
#include "model.h"
#include "Sphere.h"


/*** 
 * Coordinates and details for the floor.
 ***/
bool floor( Point3 origin, Vector3 dir ){
	// X1 : 10 , X2: 100
	// Y1 : -20 , Y2: -20
	// Z1 : -100 , Z2 : 200

	//Vector3 F( (250), (250-20),0);
	Vector3 F ( 0, 80, -550 );
	//Vector3 floor( 90, 0, 300 );
	//Vector3 floor( (99/2000), -1, (1/100));	// Calculated using 3 equations and solving the system.
	Vector3 floor( 1/70, -1, 1/200 );
	//Vector3 floor( (29/70), 1, (1/700));
	floor.normalize();

	float w = -( floor.x * origin.x + floor.y * origin.y + floor.z + origin.z + F.length() ) / (floor.x * dir.x + floor.y * dir.y + floor.z * dir.z );
	//float w = (floor * origin + F ) / (floor * dir );
	if( w > 0 ){
		Point3 poi( origin.x + dir.x * w , origin.y + dir.y * w, origin.z + dir.z * w );
		if( poi.x > 500 || poi.x < -450 )
			return false;
		else if( poi.z > -20 && poi.z < 2000 )
			return true;
	}
	return false;
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
	else if( floor(origin, dir ) ){
		glColor3f( 0, 0, 1 );
	}
	else {
		glColor3f( 0, 0, 0 );
	}

	//floor();
}