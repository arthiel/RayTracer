// model.cpp - The coordinates and model-space of the scene
// 

#include "model.h"
#include "..\vecmath.h"

/*** 
 * Coordinates and details for the mirror sphere
 ***/
GLfloat* mirror_sphere( Vector3 origin, Vector3 distance){
	// Radius : 8
	// X : 68 , Y : -5 , Z : 140
	int x = 68, y = -5, z = 140, r = 8;	 // x, y center point.

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
void model_space( void ){
	glass_sphere();
	mirror_sphere();
	floor();
}