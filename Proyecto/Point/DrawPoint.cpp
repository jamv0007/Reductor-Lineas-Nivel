
/* 
 * File:   DrawPoint.cpp
 * Author: lidia
 * 
 * Created on 14 de enero de 2021, 15:02
 */

#include "DrawPoint.h"
#include "../Renderer.h"


DrawPoint::DrawPoint (Point &p): dp (p), AG::Model(AG::TIPO_MODELO::POINT){
    

    vertices.push_back (glm::vec3(p.getX(), p.getY(), 0.0));
    indices.push_back(0);
    
    buildVAO ();
    
}

void DrawPoint::drawIt (AG::TypeColor c){
    setColor(c);
    drawIt();
}



void DrawPoint::drawIt (){
    AG::Renderer::getInstancia()->addModeloEscena(this);
    
}