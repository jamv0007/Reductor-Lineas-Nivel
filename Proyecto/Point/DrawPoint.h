
/* 
 * File:   DrawPoint.h
 * Author: lidia
 *
 * Created on 14 de enero de 2021, 15:02
 */

#ifndef DRAWPOINT_H
#define DRAWPOINT_H


#include "../Model.h"
#include "Point.h"


class DrawPoint: public AG::Model {
    Point dp;
public:
    
    DrawPoint(Point &p);
    DrawPoint (const DrawPoint &ddp): dp (ddp.dp) , AG::Model(AG::TIPO_MODELO::POINT) {}
    void drawIt ();
    void drawIt (AG::TypeColor c);
    virtual ~DrawPoint(){};

};

#endif /* DRAWPOINT_H */

