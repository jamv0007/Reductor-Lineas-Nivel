
#include "../Renderer.h"
#include "DrawTriangle3d.h"


DrawTriangle3d::DrawTriangle3d (Triangle3d &t): dt (t), AG::Model(AG::TIPO_MODELO::WIREFRAME){
    
    vertices.push_back ( glm::vec3 (dt._a.getX(), dt._a.getY() , dt._a.getZ() ) );
    vertices.push_back ( glm::vec3 (dt._b.getX(), dt._b.getY() , dt._b.getZ() ) );
    vertices.push_back ( glm::vec3 (dt._c.getX(), dt._c.getY() , dt._c.getZ() ) );

    indices.push_back ( 0 );
    indices.push_back ( 1 );
    indices.push_back ( 2 );

    buildVAO ();
    
}


void DrawTriangle3d::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawTriangle3d::drawIt (){

    AG::Renderer::getInstancia()->addModeloEscena(this);

    
}

void DrawTriangle3d::drawItPlane(AG::TypeColor c) {
    this->modelo = AG::TIPO_MODELO::PLAIN;
    setColor(c);
    AG::Renderer::getInstancia()->addModeloEscena(this);
}
