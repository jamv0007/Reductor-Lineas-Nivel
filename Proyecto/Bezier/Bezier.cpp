//
// Created by Jose Antonio on 20/2/22.
//

#include "Bezier.h"

Bezier::Bezier() {
    nVertex = 0;
}

Bezier::Bezier(int nV) {
    nVertex = nV;
}

Bezier::Bezier(const Bezier &b) {
    vVertex.clear();
    for(int i = 0; i < b.nVertex; i++){
        this->vVertex.push_back(b.vVertex[i]);
    }
    this->nVertex = b.nVertex;
}

void Bezier::add(Point p) {
    Vect2d v(p);
    vVertex.push_back(v);
    nVertex++;
}

void Bezier::add(Vect2d v) {
    vVertex.push_back(v);
    nVertex++;
}

Vect2d Bezier::getAt(int pos) {
    if(pos >= 0 && pos < nVertex){
        return vVertex[pos];
    }

    throw std::invalid_argument("Bezier::getAt -> Posicion invalida");
}

Vect2d Bezier::getCopyAt(int pos) {
    if(pos >= 0 && pos < nVertex){
        return Vect2d(vVertex[pos]);
    }

    throw std::invalid_argument("Bezier::getAt -> Posicion invalida");
}

int Bezier::size(){
    return nVertex;
}

SegmentLine Bezier::getArista(int i) {
    return SegmentLine(getAt(i), getAt((i+1) % nVertex));
}
