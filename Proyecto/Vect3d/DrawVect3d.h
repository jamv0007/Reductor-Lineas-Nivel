
/* 
 * File:   DrawVect3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 14:45
 */

#ifndef DRAWVECT3D_H
#define DRAWVECT3D_H

#include "../Model.h"
#include "Vect3d.h"


class DrawVect3d: public AG::Model {
    Vect3d dp;
public:
    
    DrawVect3d(Vect3d &p);
    DrawVect3d(std::vector<Vect3d>& p);
    DrawVect3d (DrawVect3d &ddp): dp (ddp.dp) , AG::Model(AG::TIPO_MODELO::POINT) {}
    void drawIt ();
    void drawIt (AG::TypeColor c);
    virtual ~DrawVect3d(){};

};

#endif /* DRAWVECT3D_H */

