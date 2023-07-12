//
// Created by Jose Antonio on 29/4/22.
//

#include "Box.h"

Box::Box(int x, int y ,int z):x(x),y(y),z(z) {

}

Box::~Box() {

}

Box::Box(const Box &orig) {
    this->points = orig.points;
}

Box &Box::operator=(const Box &orig) {
    this->points = orig.points;
    return *this;
}

void Box::insertPoint(Vect3d &d) {
    points.push_back(d);
}

bool Box::deletePoint(Vect3d &d) {
    auto it = points.begin();
    while (it != points.end()){
        if(*it == d){
            points.erase(it);
            return true;
        }
        it++;
    }

    return false;
}

int Box::pBox() {
    return points.size();
}

