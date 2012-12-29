/***
 * Sphere
 * Author: Emily Egeland
 * Defines a sphere in world space.
 * Computes Sphere information.
 ***/
#include "stdafx.h"
#include "Sphere.h"

	/***
	 * Constructor for Sphere
	 * x, y, z : coordinates
	 * r : radius 
	 ***/
	Sphere::Sphere( float x, float y, float z, float r ){
		// Convert previous coordinate sets to this coordinate space.
		_x = 250 + x;
		_y = 250 + y*10;
		_z = 210 + z;
		_r = r * 10;
	}
	
	Sphere::Sphere( float x, float y, float z, float r, Light ambient, Light diffuse, Light specular, float exponent){
		// Convert previous coordinate sets to this coordinate space.
		_x = 250 + x;
		_y = 250 + y*10;
		_z = 210 + z;
		_r = r * 10;

		// Light Values
		l_ambient = ambient;
		l_diffuse = diffuse;
		l_specular = specular;
		l_exponent = exponent;
	}

	void Sphere::setLighting( Light ambient, Light diffuse, Light specular, float exponent ){
		// Light Values
		l_ambient = ambient;
		l_diffuse = diffuse;
		l_specular = specular;
		l_exponent = exponent;
	}

	void Sphere::setColors( float red, float green, float blue ){
		_red = red;
		_green = green;
		_blue = blue;
	}

	/***
	 * Calculates the intersection
	 * origin : point of origin for the eye
	 * dir : direction the ray is facing
	 * returns true if intersect, false if it does not.
	 ***/
	bool Sphere::intersect( Point3 origin, Vector3 dir ){
		dir.normalize();	// Now A = 1.

		float B = 2 * ( dir.x * ( origin.x - _x ) + dir.y * ( origin.y - _y ) + dir.z * (origin.z - _z ) );
		float C = (origin.x - _x) * (origin.x - _x ) + (origin.y - _y)*(origin.y - _y) + (origin.z - _z)*(origin.z - _z) - _r *_r;  

		if( ((B * B)- 4 * C ) >= 0 ){
			glColor3f( 1, 0, 0 );
			return true;
		}
		return false;
	}

	void Sphere::phong_ambientlight(){
		_red = l_ambient._ammount * (_red * l_ambient._red);
		_green = l_ambient._ammount * (_green * l_ambient._green);
		_blue = l_ambient._ammount * (_blue * l_ambient._blue);
	}