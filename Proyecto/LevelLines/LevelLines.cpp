//
// Created by Jose Antonio on 19/5/22.
//

#include "LevelLines.h"
#include <sstream>
#include <fstream>
#include "../Vect3d/DrawVect3d.h"
#include <set>


/***
 * Funcion que devuelve un vector de string divididos por un patron
 * @param str String inicial
 * @param pattern patron
 * @return Vector del string dividido por el patron
 */
std::vector<std::string> LevelLines::split(std::string str, char pattern) {

    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<std::string> results;

    while(posFound >= 0){
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(splitted);
    }

    return results;
}


/***
 * Construtor que dado un archivo y la escala lo carga en la estructura
 * @param file Archivo
 * @param scale escala
 */
LevelLines::LevelLines(std::string &file,double scale):scale(scale) {

    std::ifstream f;
    std::string line;
    char empty = ' ';

    f.open(file,std::ios::in);

    std::vector<Vect3d> puntos;
    std::vector<DrawVect3d*> dv;
    std::set<float, std::greater<float>> height;

    int cont = 0;
    int stop = 4;
    int number = 0;

    if(!f.fail()){

        //Se obtienen el numero de puntos
        while (cont < stop) {
            std::getline(f, line);
            cont++;
        }

        std::getline(f, line);
        std::vector<std::string> n = split(line, empty);
        number = std::stoi(n[1]);

        cont = 0;

        while(cont < number) {
            std::getline(f, line);

            if (!line.empty()) {

                std::vector<std::string> res = split(line, empty);

                float x = std::stof(res[0]);
                float y = std::stof(res[2]);
                float z = std::stof(res[1]);

                Vect3d v(x, y, z);
                puntos.push_back(v);

            }


            cont++;
        }

        this->terrainCenter(&puntos);

        for(Vect3d punt: puntos){
            height.insert(punt.getY());
        }

        std::getline(f, line);
        std::vector<std::string> res = split(line, empty);
        number = std::stoi(res[1]);
        res.clear();
        cont = 0;
        while(cont < number){
            std::getline(f, line);
            res = split(line, empty);
            Level l;
            for(int i = 1; i < res.size()-1; i++){

                int pos = std::stoi(res[i]);
                int pos2 = std::stoi(res[i+1]);
                Segment3d s(puntos[pos],puntos[pos2]);
                lines.push_back(s);
                originalLine.push_back(s);
                l.addPoint(puntos[pos]);

            }

            int pos = std::stoi(res[res.size()-1]);
            l.addPoint(puntos[pos]);
            levelLines.push_back(l);

            res.clear();
            cont++;
        }

        while(!f.eof()){
            std::getline(f, line);
        }

    }else{
        throw std::runtime_error("LevelLine -> Fallo al abrir el archivo " + file);
    }

    f.close();


    auto iter = height.end();
    iter--;
    float min = *iter;
    float max = *height.begin();
    //Calculo de los colores
    std::set<float,std::greater<float>>::iterator it;
    for(it = height.end(); it != height.begin(); it--){
        float value = *it;
        Color res = getColor(value,min,max);
        this->legend.insert(std::pair<float,Color>(value,res));
    }

}

/***
 * Funcion que da un color dado un valor y un rango
 * @param v Valor
 * @param vmin Valor minimo
 * @param vmax Valor máximo
 * @return
 */
Color LevelLines::getColor(float v, float vmin, float vmax) {

    Color c(1,1,1);

    float dv;
    if (v < vmin)
        v = vmin;
    if (v > vmax)
        v = vmax;
    dv = vmax - vmin;

    if (v < (vmin + 0.25 * dv)) {
        c.setR(0);
        c.setG(4 * (v - vmin) / dv);
    } else if (v < (vmin + 0.5 * dv)) {
        c.setR(0);
        c.setB(1 + 4 * (vmin + 0.25 * dv - v) / dv);
    } else if (v < (vmin + 0.75 * dv)) {
        c.setR(4 * (v - vmin - 0.5 * dv) / dv);
        c.setB(0);
    } else {
        c.setG(1 + 4 * (vmin + 0.75 * dv - v) / dv);
        c.setB(0);
    }

    return(c);
}

/***
 * Destructor
 */
LevelLines::~LevelLines() {

}

/***
 * Funcion que devuelve el vector de segmentos
 * @return vector de segmentos
 */
std::vector<Segment3d> LevelLines::getLines() {
    return lines;
}

/***
 * Devuelve el numero de segmentos
 * @return numero de segmentos
 */
int LevelLines::getlineNumber() {
    return lines.size();
}

/***
 * Devuelve la legenda
 * @return devuelve un mapa de altura y color
 */
std::map<float, Color> LevelLines::getLegend() {
    return legend;
}

/***
 * Funcion que centra el mapa en el 0
 * @param v vector de puntos
 */
void LevelLines::terrainCenter(std::vector<Vect3d>* v) {

    //Se iteran por todos los puntos y se rellenan los mayores y menores
    double maxX = -INFINITY,maxY = -INFINITY,maxZ = -INFINITY,minX = INFINITY,minY = INFINITY,minZ = INFINITY;
    for(Vect3d vec: *v){

        if(vec.getX() > maxX){
            maxX = vec.getX();
        }
        if(vec.getX() < minX){
            minX = vec.getX();
        }
        if(vec.getY() > maxY){
            maxY = vec.getY();
        }
        if(vec.getY() < minY){
            minY = vec.getY();
        }
        if(vec.getZ() > maxZ){
            maxZ = vec.getZ();
        }
        if(vec.getZ() < minZ){
            minZ = vec.getZ();
        }
    }

    //Se calcula el centro
    Vect3d min(minX,minY,minZ);
    Vect3d max(maxX,maxY,maxZ);

    Vect3d distance(max.sub(min));
    double zMed = (distance.getZ()) / 2;
    double yMed = (distance.getY()) / 2;
    double xMed = (distance.getX()) / 2;
    Vect3d medDistance(xMed,yMed,zMed);
    Vect3d center(min.add(medDistance));


    //Se cambia la posicion desde ese centro
    for(int i = 0; i < v->size(); i++){
        Vect3d vec = v->operator[](i);
        Vect3d nPoint(vec.sub(center));
        nPoint.set(0,(nPoint.getX()*(-1)) / scale);
        nPoint.set(1,(nPoint.getY()) / scale);
        nPoint.set(2,(nPoint.getZ()) / scale);
        v->operator[](i) = nPoint;
    }




}

/***
 * Funcion que simplifica el mapa cargado dado un error
 * @param error error
 */
void LevelLines::simplifyMap(float error) {

    int cont = 0;
    lines.clear();
    for(Level l: this->levelLines){
        std::vector<Vect3d> points = l.getPoints();
        if(l.getPoint(0) == l.getPoint(l.getNumberPoints()-1)){
            //Se obtiene el punto medio
            int med = l.getNumberPoints() / 2;
            std::vector<Vect3d> v1;
            std::vector<Vect3d> v2;
            for(int i = 0; i < points.size(); i++){
                if(i < med){
                    v1.push_back(points[i]);
                }else{
                    v2.push_back(points[i]);
                }
            }

            std::vector<Vect3d> res1;
            std::vector<Vect3d> res2;
            lineSimplify(v1,error,res1);
            lineSimplify(v2,error,res2);


            res1.insert(res1.end(),res2.begin(),res2.end());

            for(int i = 0; i < res1.size()-1; i++){
                Segment3d s(res1[i],res1[i+1]);
                lines.push_back(s);
            }

        }else{
            //Si la linea no esta cerrada
            std::vector<Vect3d> res;
            lineSimplify(points,error,res);
            for(int i = 0; i < res.size()-1; i++){
                Segment3d s(res[i],res[i+1]);
                lines.push_back(s);
            }
        }


        cont++;
    }

}

/***
 * Funcion que simplifica de forma recursiva el mapa
 * @param points Puntos
 * @param error error
 * @param out vector con los puntos resultantes
 */
void LevelLines::lineSimplify(std::vector<Vect3d>& points, float error, std::vector<Vect3d>& out) {

    double maxDistance = 0;
    int index = -1;

    //Se calcula la maxima distancia al segmento entre el primero y el ultimo punto
    for(int i = 1; i < points.size()-1; i++){
        Vect3d p0 = points[i];
        Vect3d p1 = points[0];
        Vect3d p2 = points[points.size()-1];
        double distance = getSquareSegmentDistance(p0,p1,p2);

        if(distance > maxDistance){
            index = i;
            maxDistance = distance;
        }

    }

    //Si la distancia es mayor que el error
    if(maxDistance > error/scale){

        //Se repite desde el inicio al punto y del punto al final
        std::vector<Vect3d> res1;
        std::vector<Vect3d> res2;
        std::vector<Vect3d> first(points.begin(),points.begin() + index + 1);
        std::vector<Vect3d> last(points.begin() + index, points.end());
        lineSimplify(first,error,res1);
        lineSimplify(last,error,res2);

        //Se juntan los resultados
        out.assign(res1.begin(),res1.end()-1);
        out.insert(out.end(), res2.begin(),res2.end());
    }else{
        //Si es menor nos quedamos con el inicio y fin
        out.clear();
        out.push_back(points[0]);
        out.push_back(points[points.size()-1]);
    }


}

/***
 * Funcion que resetea el mapa de simplificacion
 */
void LevelLines::resetMap() {
    lines.clear();
    for(Segment3d l: originalLine){
        lines.push_back(l);
    }
}

/***
 * Funcion que devuelve la distancia a un segmento
 * @param p0 Punto origen del segmento
 * @param p1 punto
 * @param p2 Punto destino del segmento
 * @return distancia
 */
double LevelLines::getSquareSegmentDistance(Vect3d &p0, Vect3d &p1, Vect3d &p2) {

    double x0, y0, x1, y1, x2, y2;
    double dx, dy;
    double t;

    //Se calculan las distancias
    x0 = p0.getX();
    y0 = p0.getZ();

    x1 = p1.getX();
    y1 = p1.getZ();

    x2 = p2.getX();
    y2 = p2.getZ();

    dx = x2 - x1;
    dy = y2 - y1;

    //Si el punto no esta en la misma recta
    if (dx != BasicGeometry::EPSILON || dy != BasicGeometry::EPSILON) {
        //Se calcula el punto
        t = ((x0 - x1) * dx + (y0 - y1) * dy) / (dx * dx + dy * dy);
        if (t > 1.0) {
            x1 = x2;
            y1 = y2;
        } else if (t > BasicGeometry::EPSILON) {
            x1 += dx * t;
            y1 += dy * t;
        }

    }

    dx = x0 - x1;
    dy = y0 - y1;

    return dx * dx + dy * dy;
}
