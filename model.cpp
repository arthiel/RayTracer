// model.cpp - The coordinates and model-space of the scene
// 


#include "stdafx.h"
#include "model.h"

/*** 
 * Coordinates and details for the floor.
 ***/
bool floor( Point3 origin, Vector3 dir ){
	// X1 : 10 , X2: 100
	// Y1 : -20 , Y2: -20
	// Z1 : -100 , Z2 : 200

	//Vector3 F( (250), (250-20),0);
	Vector3 F ( 0, 80, origin.z );
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
	Light ambient( .8, .8, 0, .2 );
	//Light ambient( 0, 0, 0, .2 );
	Light diffuse( 1, 1, 1, .3, Point3( 500, 350, 150) );
	
	// Define world objects.
	Sphere glass( 0, .7, -235, 8 );
	glass.setColors( 0, 1, 0 );
	
	Sphere mirror( -120, -5, -140, 8 );
	mirror.setColors( 1, 0, 0 );

	glass.setLighting( ambient, diffuse, Light(), 4);
	mirror.setLighting(ambient, diffuse, Light(), 4 );
	
	// Check if intersects glass, mirror, etc.
	if( glass.intersect( origin, dir ) ){ 
		glass.phong_ambientlight();
		glass.phong_diffuselight();
		glColor3f( glass._red, glass._green, glass._blue );
		return;
	}
	else if( mirror.intersect(origin, dir )){ 
		Point3 orig( mirror._x, mirror._y, mirror._z );
		mirror.phong_ambientlight();

		// Check if mirror intersects with glass before hitting the light source.
		if( !glass.intersect( orig, (diffuse._position - orig ))){
			mirror.phong_diffuselight();
		}
		glColor3f( mirror._red, mirror._green, mirror._blue );
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