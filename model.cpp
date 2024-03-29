// model.cpp - The coordinates and model-space of the scene
// Author: Emily Egeland
// Computer Graphics II Winter 20122

#include "stdafx.h"
#include "model.h"

const int MAX_DEPTH = 4;

/***
* Calculates the ambient light effect on the sphere.
* Based on the Phong model
***/
Point phong_ambientlight(Point dot, Light amb){
    dot.l_red += amb._ammount * (dot.red * amb._red);
    dot.l_green += amb._ammount * (dot.green * amb._green);
    dot.l_blue += amb._ammount * (dot.blue * amb._blue);
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
Point light_intersect( Point pixel, Point interGlass, Point interMirror, Light source[], Vector3 dir, Sphere glass ){

    float fudge = .5;
    if( (interGlass.active && 
        ( interGlass.point.x < pixel.point.x+fudge && interGlass.point.x > pixel.point.x-fudge) &&
        ( interGlass.point.y < pixel.point.y+fudge && interGlass.point.y > pixel.point.y-fudge) &&
        ( interGlass.point.z < pixel.point.z+fudge && interGlass.point.z > pixel.point.z-fudge)))
    {
            pixel = phong_diffuselight(pixel, source[0] );
            pixel = phong_speclight(pixel, source[1], pixel.l_exponent );
    }
    else if(
        ( interMirror.active && /*!interGlass.active && */
        ( interMirror.point.x < pixel.point.x+fudge && interMirror.point.x > pixel.point.x-fudge) &&
        ( interMirror.point.y < pixel.point.y+fudge && interMirror.point.y > pixel.point.y-fudge) &&
        ( interMirror.point.z < pixel.point.z+fudge && interMirror.point.z > pixel.point.z-fudge)) ||
        ( !interMirror.active ))//&& !interGlass.active ))
    {
        pixel = phong_diffuselight(pixel, source[0] );
        pixel = phong_speclight(pixel, source[1], pixel.l_exponent );

    }
    return pixel;
}

/**
 * Check if it is in the actual intersection area of that point.
 * Using a fudge factor to approx it.
 **/
bool intersect( Point pixel, Point inter ){
    float fudge = .5;
    return  ( inter.point.x < pixel.point.x+fudge && inter.point.x > pixel.point.x-fudge) &&
            ( inter.point.y < pixel.point.y+fudge && inter.point.y > pixel.point.y-fudge) &&
            ( inter.point.z < pixel.point.z+fudge && inter.point.z > pixel.point.z-fudge);
}

/** 
 * Throw multiple reflection rays "at random" inside of a cone to approximate a BRDF.
 **/
Point cone_reflection( Sphere glass, Sphere mirror, Floor thisFloor, Point pixel, Vector3 refRay, int depth){
    
            refRay.x += .01;
            Point inter = intersection( glass, mirror, thisFloor, pixel.point, refRay, depth+1 );
            pixel.l_red += pixel.kr * inter.l_red;
            pixel.l_green += pixel.kr * inter.l_green;
            pixel.l_blue += pixel.kr * inter.l_blue;
            refRay.z += .01;

            inter = intersection( glass, mirror, thisFloor, pixel.point, refRay, depth+1 );
            pixel.l_red += pixel.kr * inter.l_red;
            pixel.l_green += pixel.kr * inter.l_green;
            pixel.l_blue += pixel.kr * inter.l_blue;
            refRay.y += .01;

            inter = intersection( glass, mirror, thisFloor, pixel.point, refRay, depth+1 );
            pixel.l_red += pixel.kr * inter.l_red;
            pixel.l_green += pixel.kr * inter.l_green;
            pixel.l_blue += pixel.kr * inter.l_blue;
            
            refRay.x -= .02;
            inter = intersection( glass, mirror, thisFloor, pixel.point, refRay, depth+1 );
            pixel.l_red += pixel.kr * inter.l_red;
            pixel.l_green += pixel.kr * inter.l_green;
            pixel.l_blue += pixel.kr * inter.l_blue;

            refRay.z -= .02;
           inter = intersection( glass, mirror, thisFloor, pixel.point, refRay, depth+1 );
            pixel.l_red += pixel.kr * inter.l_red;
            pixel.l_green += pixel.kr * inter.l_green;
            pixel.l_blue += pixel.kr * inter.l_blue;

            refRay.y -= .02;
            inter = intersection( glass, mirror, thisFloor, pixel.point, refRay, depth+1 );
            pixel.l_red += pixel.kr * inter.l_red;
            pixel.l_green += pixel.kr * inter.l_green;
            pixel.l_blue += pixel.kr * inter.l_blue;
            
            return pixel;
}

/** 
 * Find first intersection point of a ray. Put in a Point object.
 *
 * With recursion, ORIGIN will be the PIXEL, and DIR will be the RAY.
 * Without, Depth = 1.
 **/
Point intersection(Sphere glass, Sphere mirror, Floor thisFloor, Point3 origin, Vector3 dir, int depth ){
    Point pixel;
    pixel = glass.intersect( origin, dir );
   /* if( depth > 1 && dir.x > 0 ){
        pixel.setLightColors( 1, 1, 0 );
       return pixel;
    }*/

        // Define Light Sources
    Light ambient( 1, 1, 1, .2); // .2
    
    // Source 1
    Light diffuse( .5, .5, .5, 1, Point3( 300, 450, -550) );
    Light specular( 1, 1, 1, 1, Point3( 300, 450, -550 ));
    Light source1[] = { diffuse, specular };
    // If it isn't on the glass sphere, check the mirrored.
    Point inMirr = mirror.intersect( origin, dir );

    if( !pixel.active || depth != 1 ){//intersect( pixel.point, origin) || intersect( inMirr, origin ) ){// || (depth > 1 && dir.x < 0 )){
        pixel = inMirr;

        // If it isn't on mirrored sphere, check the floor.
        // depth != 1 is to ignore it on reflection.
        Point glassInt = glass.intersect(origin, dir);
        if( !pixel.active || (depth > 1 && pixel.active && !intersect( glassInt, origin)) ){ // pixel.active && (intersect( pixel.point, origin ) && depth != 1)) {//(pixel.active && !intersect( pixel, origin) && depth != 1) ) {
            pixel = thisFloor.intersect( origin, dir );

            // If it isn't on the floor, return background color.
            if( !pixel.active ) {
                //glColor3f( 0, 0, 1 );
                pixel.setColors( 0, 0, 1 );
                pixel.setLightColors( 0, 0, 1 );
                return pixel;
            } // End Floor
        } // End Mirror
        // } // End Glass
    }
    /*else if( depth > 1 && pixel.active && !intersect( pixel.point, origin) ){
        return pixel;
    }*/


    // Calculate light equations. PHONG.
    pixel = phong_ambientlight(pixel, ambient);
    Point interGlass = glass.intersect( pixel.point, (pixel.point - source1[0]._position));
    Point interMirror = mirror.intersect( pixel.point, (pixel.point - source1[0]._position) );
    pixel = light_intersect( pixel, interGlass, interMirror, source1, pixel.point - source1[0]._position, glass );

    // Stopping reflection/refraction after a certain depth.
    if( depth < MAX_DEPTH ){
        if( pixel.kr > 0 ){
            // Calculate the reflection
            Vector3 refRay = dir - 2 * pixel.surfaceNormal * ( dir * pixel.surfaceNormal );
            refRay.normalize();
            // Y is upside down.
            refRay.y *= -1;
            // Intersect recursion
            Point inter = intersection( glass, mirror, thisFloor, pixel.point, refRay, depth+1 );
            pixel.l_red += pixel.kr * inter.l_red;
            pixel.l_green += pixel.kr * inter.l_green;
            pixel.l_blue += pixel.kr * inter.l_blue;

            // Uncomment to implement reflection within a cone area. (Checkpoint 5 Extra)
            //cone_reflection( glass, mirror, thisFloor, pixel, refRay, depth );
        }
        if( pixel.kt > 0 ){
            //transmission stuff
            float nwater = 1;
            float nit = nwater /.95;
            float discrim =  1 + ( nit * nit * (pow( -dir * pixel.surfaceNormal,2) - 1 ));
            Vector3 refRay = dir;
            int count = 0;
            Point gl = pixel;

            if( discrim <= 0 ){
                 refRay = dir - 2 * gl.surfaceNormal * ( dir * gl.surfaceNormal );
                 refRay.normalize();
                 gl = glass.backIntersect( pixel.point, refRay );

                pixel.l_red += pixel.kt * gl.red;
                pixel.l_green += pixel.kt * gl.green;
                pixel.l_blue += pixel.kt * gl.blue;
                 
                 refRay = refRay - 2 * -gl.surfaceNormal * ( refRay * -gl.surfaceNormal );
                 refRay.normalize();
                 gl = glass.intersect( gl.point, refRay );
                 discrim =  1 + ( nit * nit * (pow( -refRay * -gl.surfaceNormal,2) - 1 ));

                pixel.l_red += pixel.kt * gl.l_red;
                pixel.l_green += pixel.kt * gl.l_green;
                pixel.l_blue += pixel.kt * gl.l_blue;
                 count++;
            }
            else {
                refRay = nit * refRay + ( nit * ( -refRay * gl.surfaceNormal ) - sqrt( discrim )) * gl.surfaceNormal;
                refRay.normalize();
                // Find intersection point with itself.
                gl = glass.backIntersect( pixel.point, refRay );
                nit = 0.95 / nwater;
                gl.surfaceNormal *= -1;
                discrim =  1 + ( nit * nit * (pow( -refRay * gl.surfaceNormal,2) - 1 ));

                refRay = nit * refRay + ( nit * ( -refRay * gl.surfaceNormal ) - sqrt( discrim )) * gl.surfaceNormal;
                refRay.normalize();

            }

            // Refract to the world.
            Point inter = intersection( glass, mirror, thisFloor, pixel.point, refRay, depth+1 );
            pixel.l_red += pixel.kt * inter.l_red;
            pixel.l_green += pixel.kt * inter.l_green;
            pixel.l_blue += pixel.kt * inter.l_blue;
        }
        return pixel;
    }

    return pixel;
}


/** 
 * Add more light sources. This was for Checkpoint 3. (Extra)
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

      
    // Calculate light intersections for each light source. This is source Red
    Point interGlass = glass.intersect( pixel.point, (pixel.point - sourceR[0]._position));
    Point interMirror = mirror.intersect( pixel.point, (pixel.point - sourceR[0]._position) );
    pixel = light_intersect( pixel, interGlass, interMirror, sourceR, (pixel.point - sourceR[0]._position), glass );

    // Source Green
    interGlass = glass.intersect( pixel.point, (pixel.point - sourceG[0]._position));
    interMirror = mirror.intersect( pixel.point, (pixel.point - sourceG[0]._position) );
    pixel = light_intersect( pixel, interGlass, interMirror, sourceG, (pixel.point - sourceG[0]._position), glass );

    // Source Blue
    interGlass = glass.intersect( pixel.point, (pixel.point - sourceB[0]._position));
    interMirror = mirror.intersect( pixel.point, (pixel.point - sourceB[0]._position) );
    pixel = light_intersect( pixel, interGlass, interMirror, sourceB, (pixel.point - sourceB[0]._position), glass);

    return pixel;
}

/*** 
* Position and place everything into model space.
***/
Point model_space( Point3 origin, Point3 pixelPos ){
    Vector3 dir = pixelPos - origin;

   // Define world objects.
    Sphere glass( 260, 230, 80, 80 );
    glass.setColors( .3, .3, .3);
    glass.setLightExponent( 150 );
    glass.setReflectConstant( 0 );
    glass.setTransmissionConstant( .85);

    Sphere mirror( 140, 230, 200, 80 ); // z=170, x = 160; 100, 200
    mirror.setColors( .7, .7, .7 );
    mirror.setLightExponent( 50 );
    mirror.setReflectConstant( 1 );
    mirror.setTransmissionConstant( 0 );

    Floor thisFloor = Floor();
    thisFloor.setColors( 1, 1, 0 );
    thisFloor.setLightExponent( 350 );
    thisFloor.setReflectConstant( 0 );
    thisFloor.setTransmissionConstant( 0 );


    // Finds the nearest intersection (in pixel)
    Point pixel = intersection( glass, mirror, thisFloor, origin, dir, 1 );
    if( !pixel.active ) {
        //glColor3f( 0, 0, 1 );
        pixel.setColors( 0, 0, 1 );
        pixel.setLightColors( 0, 0, 1 );
        return pixel;
    }// End Floor



    // Uncomment for Multiple Lightsources.
    // pixel = more_lightsource( pixel, glass, mirror );

    // This was moved to ray tracer file after checkpoint 6, trying
    // to keep all the gl functions in one place.
   // glColor3f( pixel.l_red, pixel.l_green, pixel.l_blue );
    
    return pixel;
}