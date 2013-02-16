#ifndef POINT_H
#define POINT_H

#include "../vecmath.h"

class Point {
public:
    Point3 point;
    Vector3 surfaceNormal;
    // material colors
    float red, green, blue;
    // light colors
    float l_red, l_green, l_blue;
    float l_exponent;

    // Reflective Constant
    float kr;
    
    // Transmission Constant
    float kt;

    // Overall Luminance for Pixel
    float luminance;

    //Active?
    bool active;

    // Constructors
    Point();
    Point( Point3 point );
    Point( Point3 point, Vector3 normal );
    Point( Point3 point, Vector3 normal, float red, float green, float blue, float exp, float refl, float trans );

    void setColors( float red, float green, float blue );
    void setLightColors( float red, float green, float blue );
    void setLightExponent( float exp );
    void setReflectConstant( float a );
    void setTransmissionConstant( float a );
    void setLuminance();

};
#endif