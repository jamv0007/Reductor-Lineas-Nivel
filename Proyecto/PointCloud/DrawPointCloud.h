
/* 
 * File:   DrawPointCloud.h
 * Author: lidia
 *
 * Created on 20 de enero de 2021, 13:29
 */

#ifndef DRAWPOINTCLOUD_H
#define DRAWPOINTCLOUD_H

#include "../Model.h"
#include "PointCloud.h"



class DrawPointCloud: public AG::Model {
    
    PointCloud dt;
    
    public:
        
    DrawPointCloud (PointCloud &t); 
    
    DrawPointCloud (const DrawPointCloud &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::POINT) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawPointCloud(){};
};



#endif /* DRAWPOINTCLOUD_H */

