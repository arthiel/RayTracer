// model.cpp - The coordinates and model-space of the scene
// 
#include "stdafx.h"
#include "model.h"


/*** 
 * Coordinates and details for the mirror sphere
 ***/
bool mirror_sphere( Vector3 origin, Vector3 dir){
	// Radius : 8
	// X : 68 , Y : -5 , Z : 140
	float x = 180, y = 200, z = 120, r = 10;	 // x, y center point.
	//float x = 20, y = 20, z = 20, r=4;
	dir.normalize();	// Now A = 1.
	//float x = 68, y = -5, z = 140, r = 8;	 // x, y center point.

	float B = 2 * ( dir.x * ( origin.x - x ) + dir.y * ( origin.y - y ) + dir.z * (origin.z - z ) );
	float C = (dir.x - x) * (dir.x -x ) + (dir.y - y)*(dir.y - y) + (dir.z - z)*(dir.z - z) - r *r;  

	if( ((B * B)- 4 * C ) >= 0 ){
		//cout << "Intersect" << endl;
		glColor3f( 1, 0, 0 );
		return true;
	}
	return false;
}

/***
 * Coordinates and details for the glass sphere
 ***/
void glass_sphere( void ){
	// Raidus 8
	// X : 80 , Y : .7 , Z : 155

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
void model_space( Vector3 origin, Vector3 distance ){
	//glass_sphere();
	distance = distance - origin;
	if( mirror_sphere( origin, distance) ){
		glColor3f( 1, 0, 0 );
	}
	else {
		glColor3f( 0, 0, 0 );
	}

	//floor();
}