
#include <iostream>
#include "Line.h"
#include "../Ray/RayLine.h"
#include "../Segment/SegmentLine.h"


Line::Line(const Point & a, const Point & b)
	: SegmentLine(a, b)
{
}

Line::Line(const Line & s)
	: SegmentLine(s)
{
}

Line::~Line()
{
}



Line & Line::operator=(const Line & line)
{
	if (this != &line)
	{
		SegmentLine::operator=(line);
	}

	return *this;
}


void Line::out()
{
	std::cout << "Line: ";
	std::cout << "Point A: ";
	this->_orig.out();
	std::cout << "Point B: ";
	this->_dest.out();
}

bool Line::intersects(Line &line, Vect2d &intersection) {
    float s,t;
    Vect2d p1(line._orig);
    Vect2d p2(line._dest);
    if(SegmentLine::intersects(p1,p2,t,s)){

        Vect2d aux = p2.minus(p1);
        Vect2d aux2 = aux.scalarMult(t);
        double y = p1.add(aux2).getY();
        double x = p1.add(aux2).getX();

        intersection.setX(x);
        intersection.setY(y);

        return true;

    }

    return false;
}

bool Line::intersects(RayLine &rayline, Vect2d &intersection) {
    float s,t;
    Vect2d p1(rayline.getA());
    Vect2d p2(rayline.getB());

    if(SegmentLine::intersects(p1,p2,t,s)){
        if(0 <= t) {
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

bool Line::intersects(SegmentLine &segment, Vect2d &intersection) {
    float s,t;
    Vect2d p1(segment.getA());
    Vect2d p2(segment.getB());

    if(SegmentLine::intersects(p1,p2,t,s)){
        if(0 <= t && t <= 1) {
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

double Line::distPointLine(Vect2d &v) {

    Vect2d P(this->_orig);
    //vector de distancia
    Vect2d d(this->_dest.minus(this->_orig));
    //Vector AP
    Vect2d AP(v.minus(P));

    float t0 = (float) ((d.dot(AP)) / d.dot(d));

    Vect2d product(d.scalarMult(t0));
    Vect2d sum(P.add(product));
    Vect2d aux(v.minus(sum));

    return (float) aux.getModule();

}
