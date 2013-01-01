// model.cpp - The coordinates and model-space of the scene
// 


#include "stdafx.h"
#include "model.h"

/*** 
* Position and place everything into model space.
***/
void model_space( Point3 origin, Point3 pixelPos ){
    //glass_sphere();
    Vector3 dir = pixelPos - origin;
    Light ambient( .1, .1, 1, .2 );
    //Light ambient( 0, 0, 0, 0 );
   // Light diffuse( 1, 1, 1, 1, Point3( 500, 350, 140) );
    Light diffuse( .5, .5, .5, 1, Point3( 600, 350, 150 ) );
    // Formerly z = -20
    Light specular( 1, 1, 1, 1, Point3( 600, 350, 150 ));

    // Define world objects.
    // z formerly -235

    Sphere glass( 260, 230, 80, 80 );
    glass.setColors( 0, 1, 0 );

    Sphere mirror( 160, 180, 170, 80 );
    mirror.setColors( 1, 0, 0 );

    glass.setLighting( ambient, diffuse, specular, 5550);
    mirror.setLighting(ambient, diffuse, specular, 350 );

    Floor thisFloor = Floor();
    thisFloor.setColors( 0, 0, 1 );

    // Check if intersects glass, mirror, etc.
    if( glass.intersect( origin, dir ) ){ 
        glass.phong_ambientlight();
        glass.phong_diffuselight();
        glass.phong_speclight();
        glColor3f( glass.l_red, glass.l_green, glass.l_blue );
        return;
    }
    else if( mirror.intersect(origin, dir )){ 
        Point3 orig( mirror._x, mirror._y, mirror._z );
        mirror.phong_ambientlight();

        // Check if mirror intersects with glass before hitting the light source.
        if( !glass.intersect( orig, (diffuse._position - orig ))){
            mirror.phong_diffuselight();
            mirror.phong_speclight();
        }
        glColor3f( mirror.l_red, mirror.l_green, mirror.l_blue );
        return;
    }
    else if( thisFloor.intersection(origin, dir ) ){
        glColor3f( 0, 0, 1 );
    }
    else {
        glColor3f( 0, 0, 0 );
    }

    //floor();
}