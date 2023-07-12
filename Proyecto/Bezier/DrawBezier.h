//
// Created by Jose Antonio on 20/2/22.
//

#ifndef PRACTICA1_AG_DRAWBEZIER_H
#define PRACTICA1_AG_DRAWBEZIER_H
#include "Bezier.h"
#include "../Model.h"


class DrawBezier: public AG::Model {
     Bezier dt;
public:

    DrawBezier (Bezier &t,int grade);

    DrawBezier (const DrawBezier &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::POINT) {}

    void drawIt ();
    void drawIt (AG::TypeColor c);

    virtual ~DrawBezier(){};

    int binomial(int n, int m);
};


#endif //PRACTICA1_AG_DRAWBEZIER_H
