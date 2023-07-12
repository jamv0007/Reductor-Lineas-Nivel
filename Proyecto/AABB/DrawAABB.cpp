

#include "DrawAABB.h"
#include "../Segment3d/DrawSegment3d.h"
#include "../Renderer.h"


DrawAABB::DrawAABB (AABB &t): _aabb (t), AG::Model(AG::TIPO_MODELO::LINE){
    
    Vect3d cero(_aabb._min.getX(),_aabb._max.getY(),_aabb._max.getZ());
    Vect3d one(_aabb._min.getX(),_aabb._min.getY(),_aabb._max.getZ());
    Vect3d two(_aabb._max.getX(),_aabb._min.getY(),_aabb._max.getZ());
    Vect3d three(_aabb._max.getX(),_aabb._max.getY(),_aabb._max.getZ());
    Vect3d four(_aabb._min.getX(),_aabb._max.getY(),_aabb._min.getZ());
    Vect3d five(_aabb._min.getX(),_aabb._min.getY(),_aabb._min.getZ());
    Vect3d six(_aabb._max.getX(),_aabb._min.getY(),_aabb._min.getZ());
    Vect3d seven(_aabb._max.getX(),_aabb._max.getY(),_aabb._min.getZ());

    vertices.push_back(glm::vec3(cero.getX(),cero.getY(),cero.getZ()));
    vertices.push_back(glm::vec3(one.getX(),one.getY(),one.getZ()));
    vertices.push_back(glm::vec3(two.getX(),two.getY(),two.getZ()));
    vertices.push_back(glm::vec3(three.getX(),three.getY(),three.getZ()));
    vertices.push_back(glm::vec3(four.getX(),four.getY(),four.getZ()));
    vertices.push_back(glm::vec3(five.getX(),five.getY(),five.getZ()));
    vertices.push_back(glm::vec3(six.getX(),six.getY(),six.getZ()));
    vertices.push_back(glm::vec3(seven.getX(),seven.getY(),seven.getZ()));

    GLuint arr[] = {1,2,0,0,3,2,7,6,2,7,2,3,4,5,6,4,6,7,4,1,5,0,1,4,0,7,3,0,4,7,2,5,1,2,0,5};

    indices.insert(indices.end(),std::begin(arr),std::end(arr));

    Segment3d a(cero,one);
    Segment3d b(one,two);
    Segment3d c(two,three);
    Segment3d d(three,cero);
    Segment3d e(four,five);
    Segment3d f(five,six);
    Segment3d g(six,seven);
    Segment3d h(seven,four);
    Segment3d i(cero,four);
    Segment3d j(one,five);
    Segment3d k(three,seven);
    Segment3d l(two,six);

    dsegment.push_back(new DrawSegment3d(a));
    dsegment.push_back(new DrawSegment3d(b));
    dsegment.push_back(new DrawSegment3d(c));
    dsegment.push_back(new DrawSegment3d(d));
    dsegment.push_back(new DrawSegment3d(e));
    dsegment.push_back(new DrawSegment3d(f));
    dsegment.push_back(new DrawSegment3d(g));
    dsegment.push_back(new DrawSegment3d(h));
    dsegment.push_back(new DrawSegment3d(i));
    dsegment.push_back(new DrawSegment3d(j));
    dsegment.push_back(new DrawSegment3d(k));
    dsegment.push_back(new DrawSegment3d(l));

    buildVAO ();
    
}


void DrawAABB::drawIt (AG::TypeColor c) {
    setColor(c);
    for (int i = 0; i < dsegment.size(); i++)
        dsegment[i]->drawIt(c);

}


void DrawAABB::drawIt (){
    
    //setShaderProgram ( "algeom" );
    //setDrawMode(TypeDraw::PolygonGeo );
    //Scene::getInstance ()->addModel ( this );
    
    for (int i=0; i<dsegment.size(); i++)
        dsegment[i]->drawIt();
    
}

void DrawAABB::drawItPlain (AG::TypeColor c) {
    setColor(c);
    setTypeModel(AG::TIPO_MODELO::PLAIN);
    drawItPlain();
}


void DrawAABB::drawItPlain (){
    setTypeModel(AG::TIPO_MODELO::PLAIN);
    AG::Renderer::getInstancia()->addModeloEscena(this);
}

