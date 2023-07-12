
/* 
 * File:   DrawCloud3d.cpp
 * Author: lidia
 * 
 * Created on 28 de enero de 2021, 12:27
 */

#include "DrawCloud3d.h"
#include "../Renderer.h"

DrawCloud3d::DrawCloud3d (PointCloud3d &t): dt (t), AG::Model(AG::TIPO_MODELO::POINT){

    for(int i = 0; i < t.size(); i++){
        vertices.push_back (glm::vec3(t.getPoint(i).getX(), t.getPoint(i).getY(), t.getPoint(i).getZ()));
        indices.push_back(i);
    }

    buildVAO ();
    
}



void DrawCloud3d::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawCloud3d::drawIt (){
    AG::Renderer::getInstancia ()->addModeloEscena(this );
    
}
void DrawCloud3d::drawItRotate(){

    this->setMatrizModelado(glm::rotate(this->getMatrizModelado(),glm::radians(-90.0f),glm::vec3(1,0,0)));
    AG::Renderer::getInstancia ()->addModeloEscena(this );

}

