/*** 
 * Floor.cpp
 * Author: Emily Egeland
 * Controls all interaction and creation for the Floor object
 ***/
#include "stdafx.h"
#include "Floor.h"


Floor::Floor(){
    front1 = Point3( 0, 0, 0 );
    front2 = Point3( 0, 0, 0 );
    back1 = Point3( 0, 0, 0 );
    back2 = Point3( 0, 0, 0 );
}
Floor::Floor( Point3 front1, Point3 front2, Point3 back1, Point3 back2 ){
    front1 = front1;
    front2 = front2;
    back1 = back1;
    back2 = back2;
}

void Floor::setColors( float red, float green, float blue ){
    red = red;
    green = green;
    blue = blue;
}

bool Floor::intersection( Point3 origin, Vector3 dir ){
    Vector3 F ( 0, 80, origin.z );

    Vector3 floor( 1/70, -1, 1/200 );
    floor.normalize();

    float w = -( floor.x * origin.x + floor.y * origin.y + floor.z + origin.z + F.length() ) / (floor.x * dir.x + floor.y * dir.y + floor.z * dir.z );
    //float w = (floor * origin + F ) / (floor * dir );
    if( w > 0 ){
        Point3 poi( origin.x + dir.x * w , origin.y + dir.y * w, origin.z + dir.z * w );
        // Checks if plane is in bounds of the floor.
        // Floor changes on X and Z values.
        if( poi.x > 500 || poi.x < -450 )
            return false;
        else if( poi.z > -20 && poi.z < 2000 )
            return true;
    }
    return false;
}