
#include "DrawSegment3d.h"
#include "../Renderer.h"

DrawSegment3d::DrawSegment3d (Segment3d &t): dt (t), AG::Model(AG::TIPO_MODELO::LINE){
    
    vertices.push_back ( glm::vec3 (dt.getOrigin().getX(), dt.getOrigin().getY() , dt.getOrigin().getZ() ) );
    vertices.push_back ( glm::vec3 (dt.getDestination().getX(), dt.getDestination().getY() , dt.getDestination().getZ() ) );

    

    indices.push_back ( 0 );
    indices.push_back ( 1 );
    

    buildVAO ();
    
}

DrawSegment3d::DrawSegment3d(std::vector<Segment3d> &s): AG::Model(AG::TIPO_MODELO::SLINE) {

    int cont = 0;
    for(Segment3d seg:s){
        vertices.push_back(glm::vec3(seg.getOrigin().getX(),seg.getOrigin().getY(),seg.getOrigin().getZ()));
        vertices.push_back(glm::vec3(seg.getDestination().getX(),seg.getDestination().getY(),seg.getDestination().getZ()));
        indices.push_back(cont);
        cont++;
        indices.push_back(cont);
        cont++;
    }

    buildVAO();
}


void DrawSegment3d::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawSegment3d::drawIt (){

    AG::Renderer::getInstancia()->addModeloEscena(this);

}

