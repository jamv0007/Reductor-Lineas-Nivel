
/* 
 * File:   DrawAABB.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 19:32
 */

#ifndef DRAWAABB_H
#define DRAWAABB_H


#include <vector>
#include "../Model.h"
#include "AABB.h"
#include "../Segment3d/DrawSegment3d.h"




class DrawAABB: public AG::Model {
    
	AABB _aabb;
	std::vector<DrawSegment3d*> dsegment;


public:
    friend class AABB;    
    
    DrawAABB (AABB &t);
    
    DrawAABB (const DrawAABB &dt): _aabb (dt._aabb), dsegment(dt.dsegment) , AG::Model(AG::TIPO_MODELO::LINE) {}
    
    void drawIt ();
    void drawIt (AG::TypeColor c);
    void drawItPlain (AG::TypeColor c);
    void drawItPlain ();
    virtual ~DrawAABB(){};
};

#endif /* DRAWAABB_H */

