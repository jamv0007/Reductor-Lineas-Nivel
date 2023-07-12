
#include "../Vect3d/Vect3d.h"
#include "DrawRay3d.h"
#include "../Renderer.h"



DrawRay3d::DrawRay3d (Ray3d &t): dt (t), AG::Model(AG::TIPO_MODELO::LINE){


    Vect3d a = dt.getOrigin();
    Vect3d b = dt.getDestination();

    Vect3d ab = b.sub(a);

    glm::vec3 ini(a.getX() + (ab.getX() * 1000),a.getY() + (ab.getY() * 1000),a.getZ() + (ab.getZ() * 1000));


    vertices.push_back ( glm::vec3(a.getX(),a.getY(),a.getZ()) );
    vertices.push_back ( ini );



    indices.push_back ( 0 );
    indices.push_back ( 1 );
    

    buildVAO ();
    
}


void DrawRay3d::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawRay3d::drawIt (){
    AG::Renderer::getInstancia()->addModeloEscena(this);
}


