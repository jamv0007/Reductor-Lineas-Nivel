//
// Created by Jose Antonio on 6/4/22.
//

#ifndef PRACTICA4_AG_VOXELMODEL_H
#define PRACTICA4_AG_VOXELMODEL_H
#include "Voxel.h"
#include "../TriangleModel/TriangleModel.h"

#include "iostream"

class VoxelModel {
    private:
        TriangleModel* model;//Modelo
        std::vector<Voxel> voxels;//Voxeles
        std::vector<bool> greyVoxel;
        AABB aabb;//AABB del modelo
        double sideTam;//Tamaño del lado del cubo
        void createExpandedAABB();
        void createVoxelModel();
    public:
        VoxelModel(TriangleModel* model, double tamVoxel);
        VoxelModel(std::string file, double tamVoxel);
        VoxelModel(const VoxelModel& orig);
        AABB getAABB();
        std::vector<Voxel> getVoxels(){
            return voxels;
        }
        std::vector<bool> getGreyVoxels(){
            return greyVoxel;
        }
        virtual ~VoxelModel();

};


#endif //PRACTICA4_AG_VOXELMODEL_H
