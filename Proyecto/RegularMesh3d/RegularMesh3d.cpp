//
// Created by Jose Antonio on 29/4/22.
//

#include "RegularMesh3d.h"

RegularMesh3d::RegularMesh3d(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, int nDiv):
xMin(xMin),xMax(xMax),yMin(yMin),yMax(yMax),zMin(zMin),zMax(zMax),nDiv(nDiv) {

    tamBoxX = (xMax - xMin) / nDiv;
    tamBoxY = (yMax - yMin) / nDiv;
    tamBoxZ = (zMax - zMin) / nDiv;


    for(int i = 0; i < nDiv; i++) {
        std::vector<std::vector<Box*>> vv;
        for(int j = 0; j < nDiv; j++){
            std::vector<Box*> v;
            for(int k = 0; k < nDiv; k++){
                Box* b = new Box(i,j,k);
                v.push_back(b);
            }

            vv.push_back(v);
        }

        boxs.push_back(vv);
    }
}

RegularMesh3d::~RegularMesh3d() {

    for(int i = 0; i < boxs.size(); i++) {
        for(int j = 0; j < boxs[i].size(); j++){
            for(int k = 0; k < boxs[i][j].size(); k++){
                delete boxs[i][j][k];
                boxs[i][j][k] = nullptr;
            }
        }

    }
}

/***
 * @brief Devuelve una caja a la que va un punto
 * @param v Punto
 * @return Puntero a la caja
 */
Box *RegularMesh3d::getBox(Vect3d &v) {

    int x = (v.getX() - xMin) / tamBoxX;
    int y = (v.getY() - yMin) / tamBoxY;
    int z = (v.getZ() - zMin) / tamBoxZ;

    return boxs[x][y][z];
}

/***
 * @brief Inserta un dato en una caja
 * @param v Punto
 */
void RegularMesh3d::insertData(Vect3d &v) {
    Box* b = getBox(v);
    b->insertPoint(v);
}

/***
 * @brief Borra un dato
 * @param v dato a borrar
 * @return Si ha sido borrado
 */
bool RegularMesh3d::deleteData(Vect3d &v) {
    Box* b = getBox(v);
    return b->deletePoint(v);
}

/***
 * @brief Obtiene las k cajas mas pobladas teniendo en cuenta la vecindad
 * @param k numero de clusters
 * @return vector de punteros a casillas
 */
std::vector<Box *> RegularMesh3d::getCentriodes(int k) {

    //Vector con pares de poblacion y la celda
    std::vector<std::pair<int,Box*>> pob;

    int pos = int(3 / 2);

    //Para cada caja se calcula la cantidad de poblacion para los nueve casillas
    for(int i = 0; i < boxs.size(); i++){//x
        for(int j = 0; j < boxs[i].size(); j++){//y
            for(int h = 0; h < boxs[i][j].size(); h++){//z
                int sum = 0;
                int level = 0;
                for(int g = 0; g < 9; g++){
                    int y = g % 3;
                    if(((i-pos + level) > -1 && (i-pos + level) < nDiv) && ((j-pos + y) > -1  &&  (j-pos + y) < nDiv))
                    {
                        sum += boxs[i-pos + level][j-pos + y][h]->pBox();
                    }
                    if(y == 2){
                        level++;
                    }
                }

                pob.push_back(std::pair<int,Box*>(sum,boxs[i][j][h]));
            }

        }
    }

    //Se ordena de mayor poblacion a menos
    std::sort(pob.rbegin(),pob.rend());


    //Se escogen los k mayores
    std::vector<Box*> centroides;

    for(int i = 0; i < k; i++){
        centroides.push_back(pob[i].second);
    }

    return centroides;

}

/*std::vector<std::vector<Vect3d*>> RegularMesh3d::createCluster(std::vector<Box *> centroides) {

    std::vector<std::vector<Vect3d*>> res;
    res.insert(res.begin(),centroides.size(),std::vector<Vect3d*>());

    for(int i = 0; i < boxs.size(); i++){
        for(int j = 0; j < boxs[i].size(); j++){
            for(int k = 0; k < boxs[i][j].size(); k++){
                float distance = INFINITY;
                int actualCluster = -1;
                for(int h = 0; h < centroides.size(); h++){
                    Box* b = centroides[h];
                    double d = sqrt(pow((b->getX() - i),2) + pow((b->getY() - j),2) + pow((b->getZ() - k),2));
                    if(d < distance){
                        distance = d;
                        actualCluster = h;
                    }
                }


                for(Vect3d v: boxs[i][j][k]->getPoints()) {
                    Vect3d * vec = new Vect3d(v);
                    res[actualCluster].push_back(vec);
                }
            }
        }
    }

    return res;
}*/

/***
 * @brief Devuelve el centro de una caja
 * @param x Posicion x de la caja (0,1,...)
 * @param y Posicion y de la caja
 * @param z Posicion z de la caja
 * @return Punto central
 */
Vect3d RegularMesh3d::getBoxCenter(int x, int y, int z) {

    double xCentral = (x * tamBoxX) + (tamBoxX / 2);
    double yCentral = (y * tamBoxY) + (tamBoxY / 2);
    double zCentral = (z * tamBoxZ) + (tamBoxZ / 2);

    return Vect3d(xCentral,yCentral,zCentral);
}

