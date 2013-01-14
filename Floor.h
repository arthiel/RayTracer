/*** 
 * Floor.h
 * Author: Emily Egeland
 * Controls all interaction and creation for the Floor object
 ***/
#ifndef FLOOR_H
#define FLOOR_H

#include "../vecmath.h"
#include <math.h>
#include "Point.h"

class Floor{
public:
    // Coordinates
    Point3 front1, front2, back1, back2;
    // Material colors
    float red, green, blue;
    // Post-Light colors
    float l_red, l_green, l_blue, l_exponent;

    // Constructors
    Floor();
    Floor( Point3 front1, Point3 front2, Point3 back1, Point3 back2 );
    
    // Set the colors
    void setColors( float red, float green, float blue );
    void setLightExponent( float exp );

    // Calculate intersection
    Point intersect( Point3 origin, Vector3 dir );

    Point texture( Point pixel );
};
#endif