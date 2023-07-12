
/* 
 * File:   DrawSegment3d.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 18:12
 */

#ifndef DRAWSEGMENT3D_H
#define DRAWSEGMENT3D_H


#include "../Model.h"
#include "Segment3d.h"


class DrawSegment3d: public AG::Model {
    
    Segment3d dt;
    
    public:
        
    DrawSegment3d (Segment3d &t);
    DrawSegment3d(std::vector<Segment3d> &s);
    DrawSegment3d (const DrawSegment3d &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::LINE) {}
    
    DrawSegment3d& operator= (const DrawSegment3d &ddt) { dt = ddt.dt; return *this;}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawSegment3d(){};
};




#endif /* DRAWSEGMENT3D_H */

