//
// Created by Jose Antonio on 19/5/22.
//

#ifndef PROYECTO_DRAWLEVELLINES_H
#define PROYECTO_DRAWLEVELLINES_H

#include <vector>
#include "../Model.h"
#include "LevelLines.h"
#include "Level.h"
#include "../Segment3d/DrawSegment3d.h"

class DrawLevelLines: public  AG::Model{

    LevelLines l;//Instancia del level lines
    DrawSegment3d* ds;//Puntero a dibujar segmentos en blanco y negro
    std::vector<DrawSegment3d*> segments;//Vector de Draw Segments
    std::map<float,std::pair<Color,std::vector<Segment3d>>> colorSegment;//Mapa de altura con un pair de color y los segmentos de ese color

public:
    friend class AABB;

    DrawLevelLines (LevelLines &t);
    DrawLevelLines(const DrawLevelLines &dt): l(dt.l) , AG::Model(AG::TIPO_MODELO::SLINE) {}

    void drawIt ();
    void drawItColor ();
    virtual ~DrawLevelLines(){};

};


#endif //PROYECTO_DRAWLEVELLINES_H
