
/* 
 * File:   DrawCloud3d.h
 * Author: lidia
 *
 * Created on 28 de enero de 2021, 12:27
 */

#ifndef DRAWCLOUD3D_H
#define DRAWCLOUD3D_H


#include "PointCloud3d.h"
#include "../Model.h"


class DrawCloud3d: public AG::Model {
    
    PointCloud3d dt;
    
    public:
        
   
    DrawCloud3d (PointCloud3d &t); 
   
    DrawCloud3d (const DrawCloud3d &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::POINT) {}
    
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    void drawItRotate();
    
    virtual ~DrawCloud3d(){};
};




#endif /* DRAWCLOUD3D_H */

