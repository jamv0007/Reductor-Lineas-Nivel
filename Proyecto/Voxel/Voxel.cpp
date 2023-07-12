//
// Created by Jose Antonio on 5/4/22.
//

#include "Voxel.h"

Voxel::Voxel():AABB() {

}

Voxel::Voxel(Vect3d min, Vect3d max): AABB(min,max) {

}

Voxel::~Voxel() {

}

Voxel::Voxel(const Voxel &orig) {
    this->voxel = orig.voxel;
    this->points = orig.points;
    this->_min = orig._min;
    this->_max = orig._max;
}

TYPE_VOXEL Voxel::getVoxel() {
    return voxel;
}

void Voxel::setVoxel(TYPE_VOXEL type) {
    this->voxel = type;
}

void Voxel::addTriangle(Triangle3d &triangle) {
    this->points.push_back(&triangle);
}



