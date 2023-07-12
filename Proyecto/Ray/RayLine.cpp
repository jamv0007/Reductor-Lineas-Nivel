
#include <iostream>
#include "RayLine.h"
#include "../Line/Line.h"


RayLine::RayLine(const Point& a, const Point& b)
	: SegmentLine(a, b)
{
}

RayLine::RayLine(const RayLine& ray)
	: SegmentLine(ray)
{
}

RayLine::~RayLine()
{
}


RayLine & RayLine::operator=(const RayLine & rayline)
{
	if (this != &rayline)
	{
		SegmentLine::operator=(rayline);
	}

	return *this;
}

void RayLine::out()
{
	std::cout<< "RayLine: ";
	SegmentLine::out();
}

bool RayLine::intersects(Line &line, Vect2d &intersection) {
    float s,t;
    Vect2d p1(line.getA());
    Vect2d p2(line.getB());
    if(SegmentLine::intersects(p1,p2,t,s)){
        if(0 <= s) {
            Vect2d aux = p2.minus(p1);
            Vect2d aux2 = aux.scalarMult(t);
            double y = p1.add(aux2).getY();
            double x = p1.add(aux2).getX();

            intersection.setX(x);
            intersection.setY(y);

            return true;
        }

    }

    return false;
}

bool RayLine::intersects(RayLine &rayline, Vect2d &intersection) {
    float s,t;
    Vect2d p1(rayline.getA());
    Vect2d p2(rayline.getB());
    if(SegmentLine::intersects(p1,p2,t,s)){
        if(0 <= s && 0 <= t) {
            Vect2d aux = p2.minus(p1);
            Vect2d aux2 = aux.scalarMult(t);
            double y = p1.add(aux2).getY();
            double x = p1.add(aux2).getX();

            intersection.setX(x);
            intersection.setY(y);

            return true;
        }

    }

    return false;
}

bool RayLine::intersects(SegmentLine &segment, Vect2d &intersection) {
    float s,t;
    Vect2d p1(segment.getA());
    Vect2d p2(segment.getB());
    if(SegmentLine::intersects(p1,p2,t,s)){
        if(0 <= s && (0 <= t && t <= 1)) {

            Vect2d aux = p2.minus(p1);
            Vect2d aux2 = aux.scalarMult(t);
            double y = p1.add(aux2).getY();
            double x = p1.add(aux2).getX();
            intersection.setX(x);
            intersection.setY(y);

            return true;
        }

    }

    return false;
}

float RayLine::distPointRayline(Vect2d &vector) {
    Vect2d P(this->_orig);
    //vector de distancia
    Vect2d d(this->_dest.minus(this->_orig));
    //Vector AP
    Vect2d AP(vector.minus(P));

    float t0 = (float) ((d.dot(AP)) / d.dot(d));

    if(t0 <= 0){
        return (float) AP.getModule();
    }else if(t0 > 0){

        Vect2d product(d.scalarMult(t0));
        Vect2d sum(P.add(product));
        Vect2d aux(vector.minus(sum));

        return (float) aux.getModule();
    }

    return 0;

}