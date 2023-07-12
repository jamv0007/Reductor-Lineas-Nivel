

#include "DrawPolygon.h"
#include "PolygonGeo.h"
#include "../Renderer.h"


DrawPolygon::DrawPolygon (PolygonGeo &t): dt (t), AG::Model(AG::TIPO_MODELO::POLYGON){
    
    for (int i=0; i<dt.getNumVertices(); i++){
        
        Point aux = dt.getVertexAt(i).getPoint();
    
        vertices.push_back(glm::vec3 (aux.getX(), aux.getY(), 0));

     
        indices.push_back ( i );
    }

    buildVAO ();
    
}


void DrawPolygon::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawPolygon::drawIt (){
    AG::Renderer::getInstancia()->addModeloEscena(this);
}
