//
// Created by Jose Antonio on 29/4/22.
//

#ifndef PRACTICA5_AG_REGULARMESH3D_H
#define PRACTICA5_AG_REGULARMESH3D_H
#include "iostream"
#include "Box.h"
#include "map"

class RegularMesh3d {
    private:
        float xMin,xMax,yMin,yMax,zMin,zMax;//Tamaño real
        float tamBoxX,tamBoxY,tamBoxZ;//Tamaño de cada caja
        int nDiv;//Nuemro de divisiones
        std::vector<std::vector<std::vector<Box*>>> boxs;//Cajas
        Box* getBox(Vect3d& v);
    public:
        RegularMesh3d(float xMin,float xMax,float yMin,float yMax,float zMin,float zMax, int nDiv);
        virtual ~RegularMesh3d();
        void insertData(Vect3d& v);
        bool deleteData(Vect3d& v);
        std::vector<Box*> getCentriodes(int k);
        //std::vector<std::vector<Vect3d*>> createCluster(std::vector<Box*> centroides);
        Vect3d getBoxCenter(int x,int y,int z);
};


#endif //PRACTICA5_AG_REGULARMESH3D_H
