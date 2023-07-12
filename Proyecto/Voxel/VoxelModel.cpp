//
// Created by Jose Antonio on 6/4/22.
//

#include "VoxelModel.h"

/***
 * Constructor con modelo
 * @param model modelo
 * @param tamVoxel lado del cubo
 */
VoxelModel::VoxelModel(TriangleModel* model, double tamVoxel) {
    this->model = model;
    this->sideTam = tamVoxel;
    createVoxelModel();



}

/***
 * Constriuctor con archivo
 * @param file Nombre archivo
 * @param tamVoxel tamaño lado
 */
VoxelModel::VoxelModel(std::string file, double tamVoxel) {
    this->model = new TriangleModel(file);
    this->sideTam = tamVoxel;
    createVoxelModel();


}

/***
 * Crea el modelo del voxel
 */
void VoxelModel::createVoxelModel() {
    //Se construye nuevo aabb
    createExpandedAABB();

    //Se calcula los cubos a poner
    AABB box(aabb);
    Vect3d max(box.getMax());
    Vect3d min(box.getMin());

    Vect3d distance(max.sub(min));
    float increment = ((float)sideTam/2.0f);
    int dX = (distance.getX() / sideTam);
    int dY = (distance.getY() / sideTam);
    int dZ = (distance.getZ() / sideTam);

    double inicialX = min.getX() + increment;
    double inicialZ = min.getZ() + increment;
    double inicialY = min.getY() + increment;

    //se itera por el aabb y  se añaden cubos
    for(int i = 0; i <= dX; i++){
        for(int j = 0; j <= dZ; j++) {
            for(int k = 0; k <= dY; k++) {
                Vect3d mm(inicialX + increment, inicialY + increment, inicialZ + increment);
                Vect3d mmi(inicialX - increment, inicialY - increment, inicialZ - increment);
                inicialY += sideTam;
                Voxel v(mmi, mm);
                voxels.push_back(v);
            }
            inicialZ += sideTam;
            inicialY = min.getY() + increment;
        }
        inicialX += sideTam;
        inicialZ = min.getZ() + increment;
    }


    //Se determina si son grises, intersenctando con los triangulos
    std::vector<Triangle3d> triangulos = model->getFaces();

    for(int i = 0 ; i < voxels.size(); i++){
        for(int j = 0; j < triangulos.size(); j++) {
            Triangle3d t = triangulos[j];
            if (voxels[i].aabbTri(t)) {
                voxels[i].addTriangle(t);
                voxels[i].setVoxel(TYPE_VOXEL::GREY);

            }


        }
        if(voxels[i].getVoxel() == TYPE_VOXEL::NP){
            voxels[i].setVoxel(TYPE_VOXEL::WHITE);
            greyVoxel.push_back(false);
        }else{
            greyVoxel.push_back(true);
        }
    }

    //Se determinan si son negros o blancos
    for(int i = 0; i < voxels.size(); i++){
        if(voxels[i].getVoxel() == TYPE_VOXEL::GREY){
            Vect3d center(voxels[i].getCenter());
            if(model->pointIntoMesh(center)){
                voxels[i].setVoxel(TYPE_VOXEL::BLACK);
            }else{
                voxels[i].setVoxel(TYPE_VOXEL::WHITE);
            }
        }else{
            Vect3d center(voxels[i].getCenter());
            if(model->pointIntoMesh(center)){
                voxels[i].setVoxel(TYPE_VOXEL::BLACK);
            }else{
                voxels[i].setVoxel(TYPE_VOXEL::WHITE);
            }
        }
    }
}

VoxelModel::~VoxelModel() {

    delete model;

}

VoxelModel::VoxelModel(const VoxelModel &orig) {
    this->voxels = orig.voxels;
    this->aabb = orig.aabb;
    this->sideTam = orig.sideTam;
    this->model = orig.model;
}

AABB VoxelModel::getAABB() {
    return aabb;
}

/***
 * Crea el nuevo aabb con un multiplo del antiguo
 */
void VoxelModel::createExpandedAABB() {

    AABB box = model->getAABB();
    Vect3d max(box.getMax());
    Vect3d min(box.getMin());
    Vect3d distance(round(max.sub(min).getX()),round(max.sub(min).getY()),round(max.sub(min).getZ()));
    Vect3d xdistance(distance.scalarMul(1.2));//* 1,2 porque sino es muy pesado con 2 directamente
    Vect3d xdistanceDiv(xdistance.getX()/2,xdistance.getY()/2,xdistance.getZ()/2);
    Vect3d center(box.getCenter());

    Vect3d newMax(center.add(xdistanceDiv));
    Vect3d newMin(center.sub(xdistanceDiv));
    this->aabb.setMax(newMax);
    this->aabb.setMin(newMin);


}