
/* 
 * File:   DrawPolygonGeo.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 12:18
 */

#ifndef DRAWPolygon_H
#define DRAWPolygon_H

#include "../Model.h"
#include "PolygonGeo.h"



class DrawPolygon : public AG::Model {
    
    PolygonGeo dt;
    
    public:
        
    DrawPolygon(PolygonGeo &t);
    
    DrawPolygon(const DrawPolygon&ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::POLYGON) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawPolygon(){};
};



#endif /* DRAWPolygonGeo_H */

