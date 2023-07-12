//
// Created by Jose Antonio on 19/5/22.
//

#include "DrawLevelLines.h"
#include "../Renderer.h"

/***
 * Constructor
 * @param t LevelLine para dibujar
 */
DrawLevelLines::DrawLevelLines(LevelLines &t): l(t), AG::Model(AG::TIPO_MODELO::LINE) {


    std::vector<Segment3d> seg = t.getLines();
    this->ds = new DrawSegment3d(seg);
    std::map<float,Color> legend = t.getLegend();

    //Se recorren los segmentos y se determina el color y se guardan
    for(Segment3d s: seg){
        float key = (float)s.getOrigin().getY();
        std::map<float,Color>::iterator it2 = legend.find(key);
        if(it2 != legend.end()) {
            if (colorSegment.count(s.getOrigin().getY())) {
                std::map<float, std::pair<Color, std::vector<Segment3d>>>::iterator it = colorSegment.find(
                        key);
                if (it != colorSegment.end()) {
                    (*it).second.second.push_back(s);
                }
            } else {
                std::vector<Segment3d> v;
                v.push_back(s);
                colorSegment.insert(std::pair<float, std::pair<Color, std::vector<Segment3d>>>(s.getOrigin().getY(),
                                                                                               std::pair<Color, std::vector<Segment3d>>(
                                                                                                       (*it2).second, v)));
            }
        }
    }

    //buildVAO();
}
/***
 * Se dibuja en blanco y negro
 */
void DrawLevelLines::drawIt() {
    ds->drawIt();

}

/***
 * Se dibuja con color
 */
void DrawLevelLines::drawItColor() {
    for(auto it = colorSegment.begin(); it != colorSegment.end(); it++){
        DrawSegment3d* drawSegment3D = new DrawSegment3d((*it).second.second);
        segments.push_back(drawSegment3D);
        Color c = (*it).second.first;
        segments[segments.size()-1]->drawIt(AG::TypeColor(c.getR(),c.getG(),c.getB()));
    }
}

