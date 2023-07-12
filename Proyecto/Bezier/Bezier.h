//
// Created by Jose Antonio on 20/2/22.
//

#ifndef PRACTICA1_AG_BEZIER_H
#define PRACTICA1_AG_BEZIER_H
#include <iostream>
#include <vector>
#include "../Vect2d/Vect2d.h"
#include "../Segment/SegmentLine.h"

class Bezier {
    protected:
        int nVertex;
        std::vector<Vect2d> vVertex;
    public:
        Bezier();
        Bezier(int nV);
        Bezier(const Bezier &b);
        void add(Vect2d v);
        void add(Point p);
        Vect2d getAt(int pos);
        Vect2d getCopyAt(int pos);
        int size();
        SegmentLine getArista(int i);
};


#endif //PRACTICA1_AG_BEZIER_H
