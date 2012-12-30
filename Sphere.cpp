/***
 * Sphere
 * Author: Emily Egeland
 * Defines a sphere in world space.
 * Computes Sphere information.
 ***/
#include "stdafx.h"
#include "Sphere.h"

	Point3 pt_intersect;

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

		float w = (B * B)- 4 * C;

		if( w >= 0 ){
			glColor3f( 1, 0, 0 );

			pt_intersect = Point3( origin.x + dir.x * w, origin.y + dir.y * w, origin.z + dir.z * w );

			return true;
		}
		return false;
	}

	void Sphere::phong_ambientlight(){
		_red = l_ambient._ammount * (_red * l_ambient._red);
		_green = l_ambient._ammount * (_green * l_ambient._green);
		_blue = l_ambient._ammount * (_blue * l_ambient._blue);
	}

	void Sphere::phong_diffuselight(){
		Vector3 norm = pt_intersect - Point3( _x, _y, _z );
		norm.normalize();
		Vector3 light = l_diffuse._position - Point3( _x, _y, _z );
		light.normalize();

		_red += l_diffuse._ammount * l_diffuse._red * ( light * norm);
		_green += l_diffuse._ammount * l_diffuse._green * ( light * norm);
		_blue += l_diffuse._ammount * l_diffuse._blue * ( light * norm);
	}

	/*void Sphere::phong_speclight(){
		
		_red += l_specular._ammount * pow(( pt_intersect ),l_exponent);
		_green += l_specular._ammount * pow(( pt_intersect ), l_exponent);
		_blue += l_specular._ammount * pow(( pt_intersect), l_exponent);
	}*/