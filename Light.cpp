#include "stdafx.h"
#include "Light.h"

Light::Light(){
	_red = 0;
	_green = 0;
	_blue = 0;
	_ammount = 0;
}

Light::Light( float red, float green, float blue, float ammount ){
	_red = red;
	_green = green;
	_blue = blue;
	_ammount = ammount;
}

Light::Light( float red, float green, float blue, float ammount, Point3 pos ){
	_red = red;
	_green = green;
	_blue = blue;
	_ammount = ammount;
	_position = pos;
}