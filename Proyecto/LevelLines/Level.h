//
// Created by Jose Antonio on 19/5/22.
//

#ifndef PROYECTO_LEVEL_H
#define PROYECTO_LEVEL_H
#include <iostream>
#include "../Vect3d/Vect3d.h"

class Level {
    private:
        std::vector<Vect3d> linePoints;//Vector con los puntos de cada nivel de altura
    public:
        Level();
        virtual ~Level();
        void addPoint(Vect3d& v);
        Vect3d getPoint(int ind);
        int getNumberPoints();
        std::vector<Vect3d> getPoints();
};


#endif //PROYECTO_LEVEL_H
