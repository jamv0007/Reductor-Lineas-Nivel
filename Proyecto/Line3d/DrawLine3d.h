
/* 
 * File:   DrawLine3d3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 17:41
 */

#ifndef DRAWLINE3D_H
#define DRAWLINE3D_H

#include "../Model.h"
#include "Line3d.h"

class DrawLine3d: public AG::Model {
    
    Line3d dt;
    
    public:
        
    DrawLine3d (Line3d &t); 
    
    DrawLine3d (DrawLine3d &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::LINE) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawLine3d(){};
};



#endif /* DRAWLINE3D_H */

