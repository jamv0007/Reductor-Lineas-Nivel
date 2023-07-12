
/* 
 * File:   DrawLine.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 12:06
 */

#ifndef DRAWLINE_H
#define DRAWLINE_H



#include "Line.h"
#include "../Model.h"

class DrawLine: public AG::Model {
    
    Line dt;
    
    public:
        
    DrawLine (Line &t); 
    
    DrawLine (const DrawLine &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::LINE) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawLine(){};
};



#endif /* DRAWLINE_H */

