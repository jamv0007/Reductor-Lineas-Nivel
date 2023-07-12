
#include "../Point/Point.h"
#include "DrawRay.h"
#include "../Renderer.h"



DrawRay::DrawRay (RayLine &t): dt (t), AG::Model(AG::TIPO_MODELO::LINE){

    Point a = dt.getA();
    Point b = dt.getB();

    Point dest((b.minus(a)).PointXScalar(100).getX(),(b.minus(a)).PointXScalar(100).getY());

    if(dest.getY() == 0){
        dest.setY(b.getY());
    }

    if(dest.getX() == 0){
        dest.setX(b.getX());
    }

    vertices.push_back ( glm::vec3 (dest.getX(),dest.getY() , 0.0 ) );
    vertices.push_back ( glm::vec3 (a.getX(), a.getY() , 0.0 ) );


    indices.push_back ( 0 );
    indices.push_back ( 1 );
    

    buildVAO ();
    
}


void DrawRay::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawRay::drawIt (){

    AG::Renderer::getInstancia()->addModeloEscena(this);

}

