#include "../Point/Point.h"
#include "DrawLine.h"
#include "Line.h"
#include "../Point/DrawPoint.h"
#include <iostream>
#include <cmath>
#include "../Renderer.h"

DrawLine::DrawLine (Line &t): dt (t), AG::Model(AG::TIPO_MODELO::LINE){

    Point a = dt.getA();
    Point b = dt.getB();

    double m = a.slope(b);

    Point dest(1000,m*1000);
    Point ini(-1000,m*(-1000));

    if(m == INFINITY){
        dest.setY(1000);
        dest.setX(b.getX());
        ini.setY(-1000);
        ini.setX(b.getX());
    }else if(m == 0){
        dest.setY(a.getY());
        ini.setY(a.getY());
    }else if(m == -INFINITY){
        dest.setY(1000);
        dest.setX(b.getX());
        ini.setY(-1000);
        ini.setX(b.getX());
    }


    vertices.push_back ( glm::vec3 (ini.getX(),ini.getY() , 0.0 ) );
    vertices.push_back ( glm::vec3 (a.getX(),a.getY() , 0.0 ) );
    vertices.push_back ( glm::vec3 (b.getX(), b.getY() , 0.0 ) );
    vertices.push_back ( glm::vec3 (dest.getX(), dest.getY() , 0.0 ) );




    indices.push_back ( 0 );
    indices.push_back ( 1 );
    indices.push_back ( 2 );
    indices.push_back ( 3 );

    buildVAO ();
    
}


void DrawLine::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawLine::drawIt (){

    AG::Renderer::getInstancia ()->addModeloEscena(this );
}


