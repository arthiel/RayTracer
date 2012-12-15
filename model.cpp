// model.cpp - The coordinates and model-space of the scene
// 
#include "stdafx.h"
#include "model.h"


/*** 
 * Coordinates and details for the mirror sphere
 ***/
bool mirror_sphere( Point3 origin, Vector3 dir){
	// Radius : 8
	// X : 68 , Y : -5 , Z : 140
	float x = 250-120, y=250-50, z= 210-140, r = 80;
	dir.normalize();	// Now A = 1.

	float B = 2 * ( dir.x * ( origin.x - x ) + dir.y * ( origin.y - y ) + dir.z * (origin.z - z ) );
	float C = (origin.x - x) * (origin.x -x ) + (origin.y - y)*(origin.y - y) + (origin.z - z)*(origin.z - z) - r *r;  

	if( ((B * B)- 4 * C ) >= 0 ){
		glColor3f( 1, 0, 0 );
		return true;
	}
	return false;
}

/***
 * Coordinates and details for the glass sphere
 ***/
bool glass_sphere( Point3 origin, Vector3 dir ){
	// Raidus 8
	// X : 80 , Y : .7 , Z : 155
	float x = 250, y = 250+7, z = 210-155-80, r = 80;	 // x, y center point.
	dir.normalize();	// Now A = 1.

	float B = 2 * ( dir.x * ( origin.x - x ) + dir.y * ( origin.y - y ) + dir.z * (origin.z - z ) );
	float C = (origin.x - x) * (origin.x -x ) + (origin.y - y)*(origin.y - y) + (origin.z - z)*(origin.z - z) - r *r;  

	if( ((B * B)- 4 * C ) >= 0 ){
		glColor3f( 0, 1, 0 );
		return true;
	}
	return false;
}

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
	if( glass_sphere( origin, dir )){
		return;//glColor3f( 0, 1, 0 );
	}
	else if( mirror_sphere( origin, dir) ){
		return;//glColor3f( 1, 0, 0 );
	}

	else {
		glColor3f( 0, 0, 0 );
	}

	//floor();
}