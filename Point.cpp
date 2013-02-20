#include "stdafx.h"
#include "Point.h"

/** 
 * If the point is not active, it is not used for much
 * It basically says it hasn't intersected with anything yet.
 **/
Point::Point(){ 
    active = false;
}

/** 
 * Set the point pixel
 **/
Point::Point( Point3 px ){
    point = px;
    active = true;
}

/**
 * Set the point, with a surface normal.
 **/
Point::Point( Point3 px, Vector3 normal ){
    point = px;
    surfaceNormal = normal;
    surfaceNormal.normalize();
    active = true;

}

/**
 * Set a Point with the surface normal, RGB colors, 
 * light exponent, reflection, and transmission properties.
 **/
Point::Point( Point3 px, Vector3 normal, float r, float g, float b , float exp, float refl, float trans){
    point = px;
    red = r;
    green = g;
    blue = b;
    setLightColors( 0, 0, 0 );

    surfaceNormal = normal;
    surfaceNormal.normalize();
    l_exponent = exp;
    kr = refl;
    kt = trans;
    active = true;
}

// Set the colors individually.
void Point::setColors( float r, float g, float b ){
   red = r;
   green = g;
   blue = b;
   setLightColors( 0, 0, 0);
}

// Set the post-lighting colors individually.
void Point::setLightColors( float r, float g, float b ){
   l_red = r;
   l_green = g;
   l_blue = b;
}

// Set light exponent
void Point::setLightExponent( float exp ){
    l_exponent = exp;
}

// Set reflection constant
void Point::setReflectConstant( float a ){
    kr = a;
}

// Set transmission constant
void Point::setTransmissionConstant( float a ){
    kt = a;
}

// Calculate & Set luminance value.
void Point::setLuminance(){
    luminance = (0.27 * l_red) + (0.67 * l_green) + (0.006 * l_blue );
}