//
// Created by Jose Antonio on 29/4/22.
//

#ifndef PRACTICA5_AG_BOX_H
#define PRACTICA5_AG_BOX_H
#include "iostream"
#include "../Vect3d/Vect3d.h"

class Box {
    private:
        std::vector<Vect3d> points;//Puntos del cubo
        int x,y,z;//Posicion del cubo
    public:
        Box(int x, int y ,int z);
        virtual ~Box();
        Box(const Box& orig);
        virtual Box& operator=(const Box& orig);
        void insertPoint(Vect3d& d);
        bool deletePoint(Vect3d& d);
        int pBox();
        int getX(){return x;};
        int getY(){return y;};
        int getZ(){return z;};
        std::vector<Vect3d> getPoints(){return points;};
};


#endif //PRACTICA5_AG_BOX_H
