#include "DrawVect3d.h"
#include "../Renderer.h"


DrawVect3d::DrawVect3d (Vect3d &p): dp (p), AG::Model(AG::TIPO_MODELO::POINT){
    
    vertices.push_back (glm::vec3(p.getX(), p.getY(), p.getZ()));

    indices.push_back(0);
    
    buildVAO ();
    
}

DrawVect3d::DrawVect3d(std::vector<Vect3d >& p): AG::Model(AG::TIPO_MODELO::POINT) {

    int cont = 0;
    for(Vect3d v: p){
        vertices.push_back(glm::vec3(v.getX(),v.getY(),v.getZ()));
        indices.push_back(cont);
        cont++;
    }

    buildVAO();

}

void DrawVect3d::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}



void DrawVect3d::drawIt (){
    AG::Renderer::getInstancia()->addModeloEscena(this);
    
}
