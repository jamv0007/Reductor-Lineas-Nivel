#include "../Point/Point.h"
#include "DrawLine3d.h"
#include "Line3d.h"
#include "../Vect2d/Vect2d.h"
#include <iostream>
#include "../Renderer.h"


DrawLine3d::DrawLine3d (Line3d &t): dt (t), AG::Model(AG::TIPO_MODELO::LINE){

    Vect3d a = dt.getOrigin();
    Vect3d b = dt.getDestination();

    Vect3d ab = b.sub(a);

    glm::vec3 ini(a.getX() + (ab.getX() * 1000),a.getY() + (ab.getY() * 1000),a.getZ() + (ab.getZ() * 1000));
    glm::vec3 fin(a.getX() + (ab.getX() * -1000),a.getY() + (ab.getY() * -1000),a.getZ() + (ab.getZ() * -1000));



    vertices.push_back ( ini );
    //_vertices.push_back ( glm::vec3 (a.getX(),a.getY() , a.getZ() ) );
    //_vertices.push_back ( glm::vec3 (b.getX(), b.getY() , b.getZ() ) );
    vertices.push_back ( fin );



    indices.push_back ( 0 );
    indices.push_back ( 1 );
    //_indices.push_back ( 2 );
    //_indices.push_back ( 3 );

    buildVAO ();
    
}


void DrawLine3d::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawLine3d::drawIt (){
    AG::Renderer::getInstancia()->addModeloEscena(this);
}



