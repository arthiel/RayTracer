/** 
 * Light sources.
 * Author: Emily Egeland
 * Computer Graphics II Winter 20122
 **/
#include "stdafx.h"
#include "Light.h"

// Sets default values
Light::Light(){
    _red = 0;
    _green = 0;
    _blue = 0;
    _ammount = 1;
}

// Sets RGB and ammount
Light::Light( float red, float green, float blue, float ammount ){
    _red = red;
    _green = green;
    _blue = blue;
    _ammount = ammount;
}

// Sets RGB, ammount, and position
Light::Light( float red, float green, float blue, float ammount, Point3 pos ){
    _red = red;
    _green = green;
    _blue = blue;
    _ammount = ammount;
    _position = pos;
}