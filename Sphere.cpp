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
    _x = x;
    _y =y;
    _z = z;
    _r = r ;
}

/***
* Constructor for Sphere
* x, y, z: Coordinates
* r : radius
* ambient, diffuse, specular, exponent: lighting related
***/
Sphere::Sphere( float x, float y, float z, float r, Light ambient, Light diffuse, Light specular, float exponent){
    // Convert previous coordinate sets to this coordinate space.
    _x = x;
    _y = y;
    _z =z;
    _r = r;

    // Light Values
    l_ambient = ambient;
    l_diffuse = diffuse;
    l_specular = specular;
    l_exponent = exponent;
}

/*** 
* Set lighting after initialization.
***/
void Sphere::setLighting( Light ambient, Light diffuse, Light specular, float exponent ){
    // Light Values
    l_ambient = ambient;
    l_diffuse = diffuse;
    l_specular = specular;
    l_exponent = exponent;
}

/*** 
* Set colors after initialization.
***/
void Sphere::setColors( float red, float green, float blue ){
    _red = red;
    _green = green;
    _blue = blue;
}

/***
* Size of the specular light on the material.
***/
void Sphere::setLightExponent( float exp ){
    l_exponent = exp;
}

/***
* Calculates the intersection
* origin : point of origin for the eye
* dir : direction the ray is facing
* returns true if intersect, false if it does not.
***/
Point Sphere::intersect( Point3 origin, Vector3 dir ){
    dir.normalize();	// Now A = 1.

    float B = 2 * ( dir.x * ( origin.x - _x ) + dir.y * ( origin.y - _y ) + dir.z * (origin.z - _z ) );
    float C = (origin.x - _x) * (origin.x - _x ) + (origin.y - _y)*(origin.y - _y) + (origin.z - _z)*(origin.z - _z) - _r *_r;  

    float w = (B * B)- 4 * C;

    // If the point intersects the sphere.
    if( w == 0 ){
        w = -B/2;
        // Store the point of intersection for later use.
        pt_intersect = Point3( origin.x + dir.x * w, origin.y + dir.y * w, origin.z + dir.z * w );

        // Return a point with the intersection, surface normal, material's red, green, and blue values, and light exponent.
        return Point( pt_intersect, (pt_intersect - Point3( _x, _y, _z)), _red, _green, _blue, l_exponent, kr, kt);
    }
    // If the point intersects the sphere twice.
    else if( w > 0 ){
        float w1 =  -(B + sqrt( w)) / 2;
        float w2 =  -(B - sqrt( w )) / 2;

        // The least positive point is the point we wish to use.
        if( w1 > w2 ){
            pt_intersect = Point3( origin.x + dir.x * w2, origin.y + dir.y * w2, origin.z + dir.z * w2 );
        }
        else {
            pt_intersect = Point3( origin.x + dir.x * w1, origin.y + dir.y * w1, origin.z + dir.z * w1 );
        }

        // Return a point with the intersection, surface normal, material's red, green, and blue values, and light exponent.
        return Point( pt_intersect, (pt_intersect - Point3( _x, _y, _z)), _red, _green, _blue, l_exponent, kr, kt);
    }
    // There is no intersection, return an empty point.
    return Point();
}

/***
* Calculates the intersection behind the first intersection.
* origin : point of origin for the eye
* dir : direction the ray is facing
* returns the exitant point of the sphere.
***/
Point Sphere::backIntersect( Point3 origin, Vector3 dir ){
    dir.normalize();	// Now A = 1.

    float B = 2 * ( dir.x * ( origin.x - _x ) + dir.y * ( origin.y - _y ) + dir.z * (origin.z - _z ) );
    float C = (origin.x - _x) * (origin.x - _x ) + (origin.y - _y)*(origin.y - _y) + (origin.z - _z)*(origin.z - _z) - _r *_r;  

    float w = (B * B)- 4 * C;

    // If the point intersects the sphere.
        float w1 =  -(B + sqrt( w)) / 2;
        float w2 =  -(B - sqrt( w )) / 2;

        // The least positive point is the point we wish to use.
        if( w1 < w2 ){
            pt_intersect = Point3( origin.x + dir.x * w2, origin.y + dir.y * w2, origin.z + dir.z * w2 );
        }
        else {
            pt_intersect = Point3( origin.x + dir.x * w1, origin.y + dir.y * w1, origin.z + dir.z * w1 );
        }

        // Return a point with the intersection, surface normal, material's red, green, and blue values, and light exponent.
        return Point( pt_intersect, (pt_intersect - Point3( _x, _y, _z)), _red, _green, _blue, l_exponent, kr, kt);

}

// Set the reflection constant
void Sphere::setReflectConstant( float a ){
    kr = a;
}

// Set the transmission constant
void Sphere::setTransmissionConstant( float a ){
    kt = a;
}