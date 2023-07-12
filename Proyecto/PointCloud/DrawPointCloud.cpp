
#include "DrawPointCloud.h"
#include "../Renderer.h"

DrawPointCloud::DrawPointCloud (PointCloud &t): dt (t), AG::Model(AG::TIPO_MODELO::POINT){

    for(int i = 0; i < t.size(); i++){
        vertices.push_back (glm::vec3(t.getPoint(i).getX(), t.getPoint(i).getY(), 0.0));
        indices.push_back(i);
    }
    buildVAO ();
    
}


void DrawPointCloud::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawPointCloud::drawIt (){
    AG::Renderer::getInstancia()->addModeloEscena(this);
    
}

