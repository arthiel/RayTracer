#include "stdafx.h"
#include "Point.h"


Point::Point(){ 
    active = false;
}

Point::Point( Point3 px ){
    point = px;
    active = true;
}

Point::Point( Point3 px, Vector3 normal ){
    point = px;
    surfaceNormal = normal;
    surfaceNormal.normalize();
    active = true;

}

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

void Point::setColors( float r, float g, float b ){
   red = r;
   green = g;
   blue = b;
   setLightColors( 0, 0, 0 );
}

void Point::setLightColors( float r, float g, float b ){
   l_red = r;
   l_green = g;
   l_blue = b;
}

void Point::setLightExponent( float exp ){
    l_exponent = exp;
}

void Point::setReflectConstant( float a ){
    kr = a;
}
void Point::setTransmissionConstant( float a ){
    kt = a;
}