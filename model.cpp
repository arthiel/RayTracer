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
    dot.setLightColors( dot.l_red, dot.l_green, dot.l_blue );

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
        dot.setLightColors( dot.l_red, dot.l_green, dot.l_blue );

    return dot;
}

/**
 * Place & Calculate lighting if there is not an object in front of it to block the 
 * light from hitting the object.
 * Pixel - point of space calculating the light of.
 * interGlass - Point of intersection with glass, if any.
 * interMirror - Point of intersection with mirror, if any.
 * source[] - the light source. [0] is diffuse [1] is specular.
 **/
Point light_intersect( Point pixel, Point interGlass, Point interMirror, Light source[] ){

    float fudge = .5;
    if( (interGlass.active && 
        ( interGlass.point.x < pixel.point.x+fudge && interGlass.point.x > pixel.point.x-fudge) &&
        ( interGlass.point.y < pixel.point.y+fudge && interGlass.point.y > pixel.point.y-fudge) &&
        ( interGlass.point.z < pixel.point.z+fudge && interGlass.point.z > pixel.point.z-fudge)) || 
        ( interMirror.active && !interGlass.active && 
        ( interMirror.point.x < pixel.point.x+fudge && interMirror.point.x > pixel.point.x-fudge) &&
        ( interMirror.point.y < pixel.point.y+fudge && interMirror.point.y > pixel.point.y-fudge) &&
        ( interMirror.point.z < pixel.point.z+fudge && interMirror.point.z > pixel.point.z-fudge)) ||
        ( !interMirror.active && !interGlass.active ))
    {
        pixel = phong_diffuselight(pixel, source[0] );
        pixel = phong_speclight(pixel, source[1], pixel.l_exponent );

    }
    return pixel;
}

/** 
 * Add more light sources. This was for Checkpoint 3.
 ***/
Point more_lightsource( Point pixel, Sphere glass, Sphere mirror ){

    // Red Light
    Light specR( 1, 0, 0, 1, Point3( 100, 150, -140 ));
    Light diffR( 1, 0, 0, 1, Point3( 100, 140, -140 ));
    Light sourceR[] = { diffR, specR };
    // Green Light
    Light diffG( 0, 1, 0, 1, Point3( 600, 450, -550) );
    Light specG( 0, 1, 0, 1, Point3( 600, 450, -550 ));
    Light sourceG[] = { diffG, specG };
    // Blue Light
    Light diffB( .1, .1, 1, 1, Point3( 300, 750, 0) );
    Light specB( .1, .1, 1, 1, Point3( 300, 750, 0 ));
    Light sourceB[] = { diffB, specB };

       
    Point interGlass = glass.intersect( pixel.point, (pixel.point - sourceR[0]._position));
    Point interMirror = mirror.intersect( pixel.point, (pixel.point - sourceR[0]._position) );
    pixel = light_intersect( pixel, interGlass, interMirror, sourceR );

    interGlass = glass.intersect( pixel.point, (pixel.point - sourceG[0]._position));
    interMirror = mirror.intersect( pixel.point, (pixel.point - sourceG[0]._position) );
    pixel = light_intersect( pixel, interGlass, interMirror, sourceG );

    interGlass = glass.intersect( pixel.point, (pixel.point - sourceB[0]._position));
    interMirror = mirror.intersect( pixel.point, (pixel.point - sourceB[0]._position) );
    pixel = light_intersect( pixel, interGlass, interMirror, sourceB);

    return pixel;
}

/*** 
* Position and place everything into model space.
***/
void model_space( Point3 origin, Point3 pixelPos ){
    Vector3 dir = pixelPos - origin;

    // Define Light Sources
    Light ambient( 1, 1, 1, .2 );
    
    // Source 1
    Light diffuse( .5, .5, .5, 1, Point3( 600, 450, -550) );
    Light specular( 1, 1, 1, 1, Point3( 600, 450, -550 ));
    Light source1[] = { diffuse, specular };


   // Define world objects.

    Sphere glass( 260, 230, 80, 80 );
    glass.setColors( 0, 1, 0 );
    glass.setLightExponent( 150 );

    Sphere mirror( 160, 180, 170, 80 );
    mirror.setColors( 1, 0, 0 );
    mirror.setLightExponent( 50 );

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
            } // End Floor
        } // End Mirror
    } // End Glass

    // Calculate light equations. PHONG.
    pixel = phong_ambientlight(pixel, ambient);
    Point interGlass = glass.intersect( pixel.point, (pixel.point - source1[0]._position));
    Point interMirror = mirror.intersect( pixel.point, (pixel.point - source1[0]._position) );
    pixel = light_intersect( pixel, interGlass, interMirror, source1 );

    // Uncomment for Multiple Lightsources.
    // pixel = more_lightsource( pixel, glass, mirror );

    glColor3f( pixel.l_red, pixel.l_green, pixel.l_blue );

    return;
}