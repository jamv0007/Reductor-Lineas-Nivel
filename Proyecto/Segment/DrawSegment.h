
/* 
 * File:   DrawSegment.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 13:10
 */

#ifndef DRAWSEGMENT_H
#define DRAWSEGMENT_H


#include "../Model.h"
#include "SegmentLine.h"



class DrawSegment: public AG::Model {
    
    SegmentLine dt;
    
    public:
        
    DrawSegment (SegmentLine &t); 
    
    DrawSegment (const DrawSegment &ddt): dt (ddt.dt) , AG::Model(AG::TIPO_MODELO::LINE) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    
    virtual ~DrawSegment(){};
};



#endif /* DRAWSEGMENT_H */

