
/* 
 * File:   DrawRay.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 20:00
 */

#ifndef DRAWRAY_H
#define DRAWRAY_H


#include "../Model.h"
#include "RayLine.h"



class DrawRay: public AG::Model {
    
    RayLine dt;
    
    public:
        
    DrawRay (RayLine &t); 
    
    DrawRay (const DrawRay &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::LINE) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawRay(){};
};



#endif /* DRAWRAY_H */

