//
// Created by Jose Antonio on 5/4/22.
//

#ifndef PRACTICA4_AG_VOXEL_H
#define PRACTICA4_AG_VOXEL_H
#include "iostream"
#include "../Vect3d/Vect3d.h"
#include "../AABB/AABB.h"

enum class TYPE_VOXEL{
    NP,WHITE,GREY,BLACK
};

class Voxel: public AABB {
    private:
        std::vector<Triangle3d*> points;
        TYPE_VOXEL voxel = TYPE_VOXEL::NP;
    public:
        Voxel();
        Voxel(Vect3d min,Vect3d max);
        Voxel(const Voxel& orig);
        virtual ~Voxel();
        void setVoxel(TYPE_VOXEL type);
        TYPE_VOXEL getVoxel();
        void addTriangle(Triangle3d& triangle);

};


#endif //PRACTICA4_AG_VOXEL_H
