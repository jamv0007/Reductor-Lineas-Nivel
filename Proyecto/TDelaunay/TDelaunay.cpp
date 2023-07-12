//
// Created by Jose Antonio on 3/5/22.
//

#include "TDelaunay.h"

TDelaunay::TDelaunay(std::string file) {

    PointCloud p(file);

    Delaunay dt;

    for(int i = 0; i < p.size(); i++){
        typePoint t(p.getPoints()[i].getX(),p.getPoints()[i].getY(),0.0f);
        dt.insert(t);
    }

    for(Delaunay::Finite_faces_iterator f = dt.finite_faces_begin(); f != dt.finite_faces_end(); f++){

        Delaunay::Face_handle face = f;
        Vect3d cero(dt.triangle(face)[0].x(),dt.triangle(face)[0].y(),dt.triangle(face)[0].z());
        Vect3d one(dt.triangle(face)[1].x(),dt.triangle(face)[1].y(),dt.triangle(face)[1].z());
        Vect3d two(dt.triangle(face)[2].x(),dt.triangle(face)[2].y(),dt.triangle(face)[2].z());

        Triangle3d t(cero,one,two);

        triangles.push_back(t);

    }
}

TDelaunay::TDelaunay(PointCloud &p) {

    Delaunay dt;


    for(int i = 0; i < p.size(); i++){
        typePoint t(p.getPoints()[i].getX(),p.getPoints()[i].getY(),0.0f);
        dt.insert(t);
    }

    for(Delaunay::Finite_faces_iterator f = dt.finite_faces_begin(); f != dt.finite_faces_end(); f++){

        Delaunay::Face_handle face = f;
        Vect3d cero(dt.triangle(face)[0].x(),dt.triangle(face)[0].y(),dt.triangle(face)[0].z());
        Vect3d one(dt.triangle(face)[1].x(),dt.triangle(face)[1].y(),dt.triangle(face)[1].z());
        Vect3d two(dt.triangle(face)[2].x(),dt.triangle(face)[2].y(),dt.triangle(face)[2].z());

        Triangle3d t(cero,one,two);

        triangles.push_back(t);

    }
}

TDelaunay::~TDelaunay() {

}

std::vector<Triangle3d> TDelaunay::getTriangles() {
    return triangles;
}