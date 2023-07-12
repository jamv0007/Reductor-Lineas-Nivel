//
// Created by Jose Antonio on 7/4/22.
//

#ifndef PRACTICA4_AG_DRAWVOXELMODEL_H
#define PRACTICA4_AG_DRAWVOXELMODEL_H
#include "VoxelModel.h"
#include "../Model.h"
#include "../AABB/DrawAABB.h"
#include "DrawVoxel.h"

class DrawVoxelModel {
    private:
        std::vector<DrawVoxel*> voxels;
        std::vector<DrawVoxel*> greyVoxels;
    public:
        DrawVoxelModel(VoxelModel &p);
        DrawVoxelModel (DrawVoxelModel &ddp): voxels(ddp.voxels) {}
        void drawIt ();
        void drawItPlane();
        void drawItPlaneAll();
        virtual ~DrawVoxelModel(){};
};


#endif //PRACTICA4_AG_DRAWVOXELMODEL_H
