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

void Floor::setColors( float r, float g, float b ){
    red = r;
    green = g;
    blue = b;
}

void Floor::setLightExponent( float exp ){
    l_exponent = exp;
}

Point Floor::intersect( Point3 origin, Vector3 dir ){
    dir.normalize();
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
            return Point();
        else if( poi.z > -20 && poi.z < 2000 )
            return texture( Point( poi, Vector3( 0, 1, 0 ), red, green, blue, l_exponent) );
    }
    return Point();
}

Point Floor::texture( Point pix){
    // If odd row 
    if( int(pix.point.z)%100 <= 50 ){
        if( pix.point.x > 0 ? int(pix.point.x)%100 <= 50 : int(-pix.point.x)%100 > 50 )
            pix.setColors( 1, 0, 0 );   // Odd Column
        else
            pix.setColors( 1, 1, 0 );   // Even Column
    }
    // If even row
    else {
        if( pix.point.x > 0 ? int(pix.point.x)%100 <= 50 : int(-pix.point.x)%100 > 50 )
            pix.setColors( 1, 1, 0 );   // Odd Column
        else
            pix.setColors( 1, 0, 0 );   // Even Column    
    }
    return pix;
}