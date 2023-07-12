
/* 
 * File:   DrawTriangleModel.h
 * Author: lidia
 *
 * Created on 21 de febrero de 2021, 11:35
 */

#ifndef DRAWTRIANGLEMODEL_H
#define DRAWTRIANGLEMODEL_H

#include "../Model.h"
#include "TriangleModel.h"

class DrawTriangleModel: public AG::Model {
    
    TriangleModel dt;
    
    public:
        
   
    DrawTriangleModel (const TriangleModel &t); 
   
    DrawTriangleModel (const DrawTriangleModel &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::WIREFRAME) {}
    
    
    void drawItPlain ();
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawTriangleModel(){};
};


#endif /* DRAWTRIANGLEMODEL_H */

