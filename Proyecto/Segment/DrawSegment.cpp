
#include "DrawSegment.h"
#include "../Renderer.h"

DrawSegment::DrawSegment (SegmentLine &t): dt (t), AG::Model(AG::TIPO_MODELO::LINE){
    
    vertices.push_back ( glm::vec3 (dt._orig.getX(), dt._orig.getY() , 0.0 ) );
    vertices.push_back ( glm::vec3 (dt._dest.getX(), dt._dest.getY() , 0.0 ) );

    indices.push_back ( 0 );
    indices.push_back ( 1 );
    

    buildVAO ();
    
}


void DrawSegment::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawSegment::drawIt (){
    AG::Renderer::getInstancia()->addModeloEscena(this);
}
