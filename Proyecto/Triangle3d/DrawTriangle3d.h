
/* 
 * File:   DrawTriangle3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 17:28
 */

#ifndef DRAWTRIANGLE3D_H
#define DRAWTRIANGLE3D_H

#include "../Model.h"
#include "Triangle3d.h"



class DrawTriangle3d: public AG::Model {
    
    Triangle3d dt;
    
    public:
        
    DrawTriangle3d (Triangle3d &t); 
    
    DrawTriangle3d (DrawTriangle3d &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::WIREFRAME) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    void drawItPlane (AG::TypeColor c);
    
    virtual ~DrawTriangle3d(){};
};


#endif /* DRAWTRIANGLE3D_H */

