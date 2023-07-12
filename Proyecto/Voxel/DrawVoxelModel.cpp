//
// Created by Jose Antonio on 7/4/22.
//

#include "DrawVoxelModel.h"

DrawVoxelModel::DrawVoxelModel(VoxelModel &p) {

    for(int i = 0; i < p.getVoxels().size(); i++){
        Voxel v(p.getVoxels()[i]);
        DrawVoxel *dv = new DrawVoxel(v);
        voxels.push_back(dv);
        Voxel v2(v.getMin(),v.getMax());

        if(p.getGreyVoxels()[i]){
            v2.setVoxel(TYPE_VOXEL::GREY);
        }else{
            v2.setVoxel(TYPE_VOXEL::WHITE);
        }
        DrawVoxel *dvg = new DrawVoxel(v2);
        greyVoxels.push_back(dvg);
    }
}

void DrawVoxelModel::drawIt() {
    for(int i = 0; i < voxels.size(); i++){
        voxels[i]->drawIt();
    }
}


void DrawVoxelModel::drawItPlane() {
    for(int i = 0; i < voxels.size(); i++){
        voxels[i]->drawItPlane();
    }
}

void DrawVoxelModel::drawItPlaneAll() {
    for(int i = 0; i < greyVoxels.size(); i++){
        greyVoxels[i]->drawItPlaneAll();
    }
}



