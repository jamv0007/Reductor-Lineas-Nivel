//
// Created by Jose Antonio on 19/5/22.
//

#include "Level.h"

/***
 * Constructor
 */
Level::Level() {

}

/***
 * Destructor
 */
Level::~Level() {

}

/***
 * Añadir punto a la linea
 * @param v Punto
 */
void Level::addPoint(Vect3d &v) {
    linePoints.push_back(v);
}

/***
 * Devolver punto en posicion
 * @param ind indice
 * @return Punto
 */
Vect3d Level::getPoint(int ind) {
    if(ind > -1 && ind < linePoints.size()){
        return linePoints[ind];
    }

    return Vect3d();
}

/***
 * Devuelve el numero de puntos
 * @return numero de puntos
 */
int Level::getNumberPoints() {
    return linePoints.size();
}
/***
 * Devuelve un vector de puntos
 * @return vector de puntos
 */
std::vector<Vect3d> Level::getPoints() {
    return linePoints;
}