
#include "../Renderer.h"
#include "DrawTriangle.h"


DrawTriangle::DrawTriangle (Triangle &t): dt (t), AG::Model(AG::TIPO_MODELO::WIREFRAME){
    
    vertices.push_back ( glm::vec3 (dt.a.getX(), dt.a.getY() , 0.0 ) );
    vertices.push_back ( glm::vec3 (dt.b.getX(), dt.b.getY() , 0.0 ) );
    vertices.push_back ( glm::vec3 (dt.c.getX(), dt.c.getY() , 0.0 ) );


    indices.push_back ( 0 );
    indices.push_back ( 1 );
    indices.push_back ( 2 );

    buildVAO ();
    
}


void DrawTriangle::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawTriangle::drawIt (){

    AG::Renderer::getInstancia()->addModeloEscena(this);

    
}