/*** 
 * Floor.cpp
 * Author: Emily Egeland
 * Controls all interaction and creation for the Floor object
 ***/
#include "stdafx.h"
#include "Floor.h"


// Default floor points.
Floor::Floor(){
    front1 = Point3( 0, 0, 0 );
    front2 = Point3( 0, 0, 0 );
    back1 = Point3( 0, 0, 0 );
    back2 = Point3( 0, 0, 0 );
}

// Set the floor points.
Floor::Floor( Point3 front1, Point3 front2, Point3 back1, Point3 back2 ){
    front1 = front1;
    front2 = front2;
    back1 = back1;
    back2 = back2;
}

// Set colors of the floor.
void Floor::setColors( float r, float g, float b ){
    red = r;
    green = g;
    blue = b;
}

// Set light exponent
void Floor::setLightExponent( float exp ){
    l_exponent = exp;
}

// Calculates the intersection point with the floor
Point Floor::intersect( Point3 origin, Vector3 dir ){
    dir.normalize();
    Vector3 F ( 0, 80, origin.z );

    Vector3 floor( 1/70, -1, 1/200 );
    floor.normalize();

    float w = -( floor.x * origin.x + floor.y * origin.y + floor.z + origin.z + F.length() ) / (floor.x * dir.x + floor.y * dir.y + floor.z * dir.z );
    //float w = (floor * origin + F ) / (floor * dir );
    if( w > 0 ){
        Point3 poi( origin.x + dir.x * w , 80 /*origin.y + dir.y * w*/, origin.z + dir.z * w );
        // Checks if plane is in bounds of the floor.
        // Floor changes on X and Z values.
        if( poi.x > 500 || poi.x < -450 )
            return Point();
        else if( poi.z > -20 && poi.z < 2000 )
            return checker( Point( poi, Vector3( 0, 1, 0 ), red, green, blue, l_exponent, kr, kt), 50 );
            // Uncomment for a diagonal Pattern. (Extra, Checkpoint 4)
            return diagonal( Point( poi, Vector3( 0, 1, 0 ), red, green, blue, l_exponent, kr, kt), 50 );
    }
    return Point();
}

// Creates a checker pattern on the floor.
Point Floor::checker( Point pix, int size){
    // If odd row 
    if( int(pix.point.z)%(size*2) <= size ){
        if( pix.point.x > 0 ? int(pix.point.x)%(size*2) <= size : int(-pix.point.x)%(size*2) > size)
            pix.setColors( 1, 0, 0 );   // Odd Column
        else
            pix.setColors( 1, 1, 0 );   // Even Column
    }
    // If even row
    else {
        if( pix.point.x > 0 ? int(pix.point.x)%(size*2) <= size : int(-pix.point.x)%(size*2) > size )
            pix.setColors( 1, 1, 0 );   // Odd Column
        else
            pix.setColors( 1, 0, 0 );   // Even Column    
    }
    return pix;
}

/**
 * Simplifies the mod value to smaller text-area.
 **/
int Floor::modX( int x, int size ){
    return int(x)%(size*2);
}

/** 
 * Creates a diagonal pattern on the floor
 **/
Point Floor::diagonal( Point pix, int size ){
    float px = pix.point.x;
    float pz = pix.point.z;

    // (size*2)-modX(-px,size) converts the x point when it crosses over to the negative values.

    // If odd row 
    if( modX(pz, size) <= size ){
        if( px > 0 ? modX(px, size) <= size : (size*2)-modX(-px, size) <= size){ // Odd Column
            if( px > 0 ? modX( px, size ) <= modX( pz, size ) : (size*2)-modX(-px, size ) <= modX(pz, size) ){
                pix.setColors( 1, 0, 0 );   
            }
            else {
                pix.setColors( 1, 1, 0 );
            }
        }
        else{ // Even Column
            if( px > 0 ? modX( px, size/2 ) >= modX( pz, size ) : (size)-modX(-px, size) >= modX(pz, size) ){
                pix.setColors( 1, 0, 0 );
            }
            else {
                pix.setColors( 1, 1, 0 );
            }
        }
    }
    // If even row
    else {
        if( px > 0 ? modX(px,size) <= size : (size*2)-modX(-px, size) <= size ){ // Odd Column
            // If X and Z are equivalent, or Z is greater than X, make it red. This creates a triangle in the upper left.
            if( px > 0 ? modX( px, size ) >= modX( pz, size/2 ) : (size*2)-modX(-px, size ) > modX(pz, size/2) ){
                pix.setColors( 1, 0, 0 );   
            }
            else {
                pix.setColors(1, 1, 0 );
            }
        }
        else{ // Even Column
            // If X and Z are equivalent, or Z is less than X, make it red. This creates a triangle in the lower right.
            if( px > 0 ? modX( px, size ) <= modX( pz, size ) : (size*2)-modX(-px, size) < modX(pz, size) ){
                pix.setColors( 1, 0, 0 );   
            }
            else {
                pix.setColors( 1, 1, 0 );
            }        
        }
    }
    return pix;
}

// Sets the reflection constant for the whole floor
void Floor::setReflectConstant( float a ){
    kr = a;
}

// Sets the Transmission constant for the whole floor
void Floor::setTransmissionConstant( float a ){
    kt = a;
}