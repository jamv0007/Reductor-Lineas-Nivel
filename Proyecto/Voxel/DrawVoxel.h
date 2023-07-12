//
// Created by Jose Antonio on 10/4/22.
//

#ifndef PRACTICA4_AG_DRAWVOXEL_H
#define PRACTICA4_AG_DRAWVOXEL_H
#include "Voxel.h"
#include "../Model.h"

class DrawVoxel {
private:
    Voxel voxel;
public:
    DrawVoxel(Voxel &p);
    DrawVoxel (DrawVoxel &ddp): voxel(ddp.voxel) {}
    void drawIt ();
    void drawItPlane();
    void drawItPlaneAll();
    virtual ~DrawVoxel(){};
};


#endif //PRACTICA4_AG_DRAWVOXEL_H
