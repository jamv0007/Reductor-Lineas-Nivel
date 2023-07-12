
/* 
 * File:   DrawPlane.cpp
 * Author: lidia
 * 
 * Created on 28 de enero de 2021, 17:11
 */


#include "DrawPlane.h"
#include "../Renderer.h"
#include "../Segment3d/DrawSegment3d.h"



DrawPlane::DrawPlane (Plane &t): dt (t), AG::Model(AG::TIPO_MODELO::POLYGON){
    //Se dibuja extendiendo las aristas del triangulo que forman
    //siempre estando p abajo de q y r a la izquierda
    /*
     * q
            * r
     * p
     */
    Vect3d p(dt.getP());
    Vect3d q(dt.getQ());
    Vect3d r(dt.getR());

    Vect3d pq(q.sub(p));
    Vect3d pr(r.sub(p));
    Vect3d qr(r.sub(q));

    float tam = 7;//tamaño de extension

    //calculo de extensiones
    Vect3d pqPos(p.getX() + (pq.getX() * tam),p.getY() + (pq.getY() * tam),p.getZ() + (pq.getZ() * tam));
    Vect3d pqNeg(p.getX() + (pq.getX() * -tam),p.getY() + (pq.getY() * -tam),p.getZ() + (pq.getZ() * -tam));
    Vect3d prPos(p.getX() + (pr.getX() * tam),p.getY() + (pr.getY() * tam),p.getZ() + (pr.getZ() * tam));
    Vect3d prNeg(p.getX() + (pr.getX() * -tam),p.getY() + (pr.getY() * -tam),p.getZ() + (pr.getZ() * -tam));
    Vect3d qrPos(q.getX() + (qr.getX() * tam),q.getY() + (qr.getY() * tam),q.getZ() + (qr.getZ() * tam));
    Vect3d qrNeg(q.getX() + (qr.getX() * -tam),q.getY() + (qr.getY() * -tam),q.getZ() + (qr.getZ() * -tam));

    //Muestra extensiones
    /*Segment3d a(pqPos,pqNeg);
    Segment3d b(prPos,prNeg);
    Segment3d c(qrPos,qrNeg);

    DrawSegment3d *da = new DrawSegment3d(a);
    DrawSegment3d *db = new DrawSegment3d(b);
    DrawSegment3d *dc = new DrawSegment3d(c);

    da->drawIt(AG::TypeColor(255,0,0));
    db->drawIt(AG::TypeColor(0,255,0));
    dc->drawIt(AG::TypeColor(0,0,255));*/



    //Se guardan los puntos
    glm::vec3 P1(qrNeg.getX(),pqPos.getY(),pqPos.getZ());
    glm::vec3 P2(qrNeg.getX(),pqNeg.getY(),pqNeg.getZ());
    glm::vec3 P3(qrPos.getX(),pqNeg.getY(),pqNeg.getZ());
    glm::vec3 P4(qrPos.getX(),pqPos.getY(),pqPos.getZ());


    vertices.push_back(P1);
    vertices.push_back(P2);
    vertices.push_back(P3);
    vertices.push_back(P4);


    indices.push_back ( 0 );
    indices.push_back ( 1 );
    indices.push_back ( 2 );
    indices.push_back ( 3 );


     buildVAO ();
    
}

DrawPlane::DrawPlane(Plane &t, std::vector<Vect3d> v):dt(t), AG::Model(AG::TIPO_MODELO::POLYGON) {
    //Se dibuja el plano con los extremos siempre que esten en el plano
    std::vector<glm::vec3> vert;

    int cont = 0;
    for(int i = 0; i < v.size(); i++){
        if(((t.getA() * v[i].getX()) + (t.getB() * v[i].getY()) + (t.getC() * v[i].getZ()) + t.getD()) == 0 ){
            vertices.push_back(glm::vec3(v[i].getX(),v[i].getY(),v[i].getZ()));
            indices.push_back(cont);
            cont++;
        }
    }

    buildVAO ();


}

DrawPlane::DrawPlane(Plane &t, std::vector<Vect2d> v):dt(t), AG::Model(AG::TIPO_MODELO::POLYGON) {


    for(int i = 0; i < v.size(); i++){
        double y = ((-1 * v[i].getX() * t.getA()) - (v[i].getY() * t.getC()) - t.getD()) / t.getB();
        

        vertices.push_back(glm::vec3(v[i].getX(),y,v[i].getY()));
        indices.push_back(i);
    }

    buildVAO();
}


void DrawPlane::drawIt (AG::TypeColor c){
    setColor (c);
    drawIt();
}


void DrawPlane::drawIt (){
    AG::Renderer::getInstancia()->addModeloEscena(this);

    
}

