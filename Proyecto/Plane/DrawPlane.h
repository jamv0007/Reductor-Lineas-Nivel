
/* 
 * File:   DrawPlane.h
 * Author: lidia
 *
 * Created on 28 de enero de 2021, 17:11
 */

#ifndef DRAWPLANE_H
#define DRAWPLANE_H

#include "../Model.h"
#include "Plane.h"


class DrawPlane: public AG::Model {
    
    Plane dt;
    
    public:
        
    DrawPlane (Plane &t);
    DrawPlane (Plane &t, std::vector<Vect3d> v);
    DrawPlane (Plane &t, std::vector<Vect2d> v);
    DrawPlane (const DrawPlane &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::POLYGON) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawPlane(){};
};

#endif /* DRAWPLANE_H */

