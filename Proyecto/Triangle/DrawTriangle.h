
/* 
 * File:   DrawTriangle.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 14:11
 */

#ifndef DRAWTRIANGLE_H
#define DRAWTRIANGLE_H

//#include "Scene.h"
#include "Triangle.h"
#include "../Model.h"


class DrawTriangle: public AG::Model {
    
    Triangle dt;
    
    public:
        
    DrawTriangle (Triangle &t); 
    
    DrawTriangle (const DrawTriangle &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::WIREFRAME) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawTriangle(){};
};


#endif /* DRAWTRIANGLE_H */

