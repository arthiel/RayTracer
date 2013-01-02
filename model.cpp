// model.cpp - The coordinates and model-space of the scene
// 

#include "stdafx.h"
#include "model.h"

/***
* Calculates the ambient light effect on the sphere.
* Based on the Phong model
***/
Point phong_ambientlight(Point dot, Light amb){
    dot.l_red = amb._ammount * (dot.red * amb._red);
    dot.l_green = amb._ammount * (dot.green * amb._green);
    dot.l_blue = amb._ammount * (dot.blue * amb._blue);
    dot.setLightColors( dot.l_red, dot.l_green, dot.l_blue );
    return dot;
}

/*** 
* Calculates the diffuse light effect on the sphere.
* Based on the Phong model, adds light result to Ambient.
***/
Point phong_diffuselight(Point dot, Light diffuse){
    // Calculate the direction the light is coming from.
    Vector3 lightDir = diffuse._position - dot.point;
    lightDir.normalize();

    // Add the diffuse lighting to the ambient lighting.
    dot.l_red += diffuse._ammount * (diffuse._red * dot.red ) * ( lightDir * dot.surfaceNormal);
    dot.l_green += diffuse._ammount * (diffuse._green * dot.green ) * ( lightDir * dot.surfaceNormal);
    dot.l_blue += diffuse._ammount * (diffuse._blue * dot.blue ) * ( lightDir * dot.surfaceNormal);
    return dot;
}

Point phong_speclight(Point dot, Light spec, float exponent){
    // Calculate the light direction
    Vector3 lightDir = spec._position - dot.point;
    lightDir.normalize();
    // Calculate direction of light reflection.
    Vector3 reflect = lightDir - 2 * ( ( lightDir * dot.surfaceNormal ) / ( dot.surfaceNormal * dot.surfaceNormal ) ) * dot.surfaceNormal;
    reflect.normalize();

    // Change from these numbers later, taken from RayTracer Origin
    Point3 origin( 250, 250, 550 );
    Vector3 org = origin - dot.point;
    org.normalize();

    // Add specular lighting to the ambient and diffuse.
    dot.l_red += spec._ammount * (spec._red * dot.red) * pow(( reflect * org ), exponent);
    dot.l_green += spec._ammount * (spec._green * dot.green) *  pow(( reflect * org ), exponent);
    dot.l_blue += spec._ammount * (spec._blue * dot.blue) * pow(( reflect * org), exponent);
    return dot;
}

/*** 
* Position and place everything into model space.
***/
void model_space( Point3 origin, Point3 pixelPos ){
    //glass_sphere();
    Vector3 dir = pixelPos - origin;
   // Light ambient( .1, .1, 1, .2 );
    Light ambient( 0, 0, 0, 1 );
    Light diffuse( 1, 1, 1, 1, Point3( 300, 350, 150) );
   // Light diffuse( .5, .5, .5, 1, Point3( 600, 350, -150 ) );
    // Formerly z = -20
    //Light specular( 1, 1, 1, 1, Point3( 600, 350, 150 ));
    Light specular( 0, 0, 0, 1, Point3( 600, 350, 150 ));
    // Define world objects.
    // z formerly -235

    Sphere glass( 260, 230, 80, 80 );
    glass.setColors( 0, 1, 0 );
    glass.setLightExponent( 5550 );

    Sphere mirror( 160, 180, 170, 80 );
    mirror.setColors( 1, 0, 0 );
    mirror.setLightExponent( 350 );

   // glass.setLighting( ambient, diffuse, specular, 5550);
   // mirror.setLighting(ambient, diffuse, specular, 350 );

    Floor thisFloor = Floor();
    thisFloor.setColors( 1, 1, 0 );
    thisFloor.setLightExponent( 350 );

    Point pixel;
    pixel = glass.intersect( origin, dir );

    // If it isn't on the glass sphere, check the mirrored.
    if( !pixel.active ){
        pixel = mirror.intersect( origin, dir );
        // If it isn't on mirrored sphere, check the floor.
        if( !pixel.active ){
            pixel = thisFloor.intersect( origin, dir );
            // If it isn't on the floor, return background color.
            if( !pixel.active ) {
                glColor3f( 0, 0, 1 );
                return;
            }
        }
    }
    // Pixel is now set, now perform Phong on it.

        pixel = phong_ambientlight(pixel, ambient);
        pixel = phong_diffuselight(pixel, diffuse);
        pixel = phong_speclight(pixel, specular, pixel.l_exponent);

        glColor3f( pixel.l_red, pixel.l_green, pixel.l_blue );
        
        return;
}