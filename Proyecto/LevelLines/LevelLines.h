//
// Created by Jose Antonio on 19/5/22.
//

#ifndef PROYECTO_LEVELLINES_H
#define PROYECTO_LEVELLINES_H
#include <iostream>
#include "../Vect3d/Vect3d.h"
#include "../Segment3d/Segment3d.h"
#include "../Color.h"
#include "Level.h"
#include <map>

class LevelLines {
    private:
        double scale = 1000;//Escala
        std::vector<Segment3d> lines;//Vector con los segmentos del mapa de altura que se usa para dibujar y que se modifica
        std::vector<Segment3d> originalLine;//Vector con segmentos sin modificar
        std::vector<Level> levelLines;//Vector con elementos de niveles
        std::map<float, Color> legend;//Mapa con las alturas y color asignado
        std::vector<std::string> split(std::string str, char pattern);//Funcion para obtener un string en partes por un patron
        Color getColor(float v, float vmin,float vmax);//Funcion que devuelve un color daada un valor y el rango en el que puede estar
        void lineSimplify(std::vector<Vect3d>& points, float error, std::vector<Vect3d>& out);//Funcion que simplifica de forma recursiva
        double getSquareSegmentDistance(Vect3d& p0,Vect3d& p1, Vect3d& p2);//Funcion que da la distancia de un punto a un segmento
        bool simplify = false;//Indica si esta simplificado
    public:
        LevelLines(std::string& file, double scale);
        virtual ~LevelLines();
        void simplifyMap(float error);
        int getlineNumber();
        void terrainCenter(std::vector<Vect3d>* v);
        std::vector<Segment3d> getLines();
        std::map<float,Color> getLegend();
        bool isSimplify(){ return simplify;};
        void setSimplify(bool value){simplify = value;};
        void resetMap();
};


#endif //PROYECTO_LEVELLINES_H
