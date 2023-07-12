#include <cmath>
#include <iostream>
#include "SegmentLine.h"
#include "../Line/Line.h"
#include "../Ray/RayLine.h"


SegmentLine::SegmentLine()
{
}

SegmentLine::SegmentLine(const Point& a, const Point& b)
	: _orig(a), _dest(b)
{
}

SegmentLine::SegmentLine(const SegmentLine& segment)
	: _orig(segment._orig), _dest(segment._dest)
{
}

SegmentLine::SegmentLine(double ax, double ay, double bx, double by)
	: _orig(ax, ay), _dest(bx, by)
{
}

SegmentLine::~SegmentLine()
{
}

float SegmentLine::distPointSegment(Vect2d &vector) {

    Vect2d P(this->_orig);

    //vector de distancia
    Vect2d d(this->_dest.minus(this->_orig));
    //Vector AP
    Vect2d AP(vector.minus(P));

    float t0 = (float) ((d.dot(AP)) / d.dot(d));

    if(t0 <= 0){
        return (float) AP.getModule();
    }else if(0 < t0 && t0 < 1){
        Vect2d product(d.scalarMult(t0));
        Vect2d sum(P.add(product));
        Vect2d aux(vector.minus(sum));
        return (float) aux.getModule();
    }else if(t0 >= 1){
        Vect2d sum(P.add(d));
        Vect2d aux(vector.minus(sum));
        return (float) aux.getModule();
    }


    return 0;
}

bool SegmentLine::intersects(Vect2d &p1, Vect2d &p2, float &t, float &s) {
    Vect2d a(this->_orig);
    Vect2d b(this->_dest);

    Vect2d ab = b.minus(a);
    Vect2d cd = p2.minus(p1);
    Vect2d ac = p1.minus(a);

    double ds = (cd.getX() * ab.getY()) - (ab.getX() * cd.getY());

    if(ds == BasicGeometry::EPSILON){
        return false;
    }

    double dt = ds;

    s = ((cd.getX() * ac.getY()) - (ac.getX() * cd.getY())) / ds;
    t = ((ab.getX() * ac.getY()) - (ac.getX() * ab.getY())) / dt;

    return true;
}

bool SegmentLine::intersects(Line r, Vect2d& intersect) {

    float s,t;
    Vect2d p1(r._orig);
    Vect2d p2(r._dest);
    if(this->intersects(p1,p2,t,s)){
        if((0 <= s) && (s <= 1)){
            Vect2d aux = p2.minus(p1);
            Vect2d aux2 = aux.scalarMult(t);
            double y = p1.add(aux2).getY();
            double x = p1.add(aux2).getX();

            intersect.setX(x);
            intersect.setY(y);

            return true;
        }
    }

    return false;

}

bool SegmentLine::intersects(RayLine r, Vect2d &intersect) {
    float s,t;
    Vect2d p1(r._orig);
    Vect2d p2(r._dest);
    if(this->intersects(p1,p2,t,s)){
        if(((0 <= s) && (s <= 1)) && (0 <= t)){
            Vect2d aux = p2.minus(p1);
            Vect2d aux2 = aux.scalarMult(t);
            double y = p1.add(aux2).getY();
            double x = p1.add(aux2).getX();

            intersect.setX(x);
            intersect.setY(y);

            return true;
        }
    }

    return false;
}

bool SegmentLine::intersects(SegmentLine r, Vect2d &intersect) {
    float s,t;
    Vect2d p1(r._orig);
    Vect2d p2(r._dest);
    if(this->intersects(p1,p2,t,s)){
        if(((0 <= s) && (s <= 1)) && ((0 <= t) && (t <= 1))){
            Vect2d aux = p2.minus(p1);
            Vect2d aux2 = aux.scalarMult(t);
            double y = p1.add(aux2).getY();
            double x = p1.add(aux2).getX();

            intersect.setX(x);
            intersect.setY(y);

            return true;
        }
    }

    return false;
}

SegmentLine & SegmentLine::operator=(const SegmentLine & segment)
{
	if (this != &segment)
	{
		this->_orig = segment._orig;
		this->_dest = segment._dest;
	}

	return *this;
}



bool SegmentLine::distinct(SegmentLine & segment)
{
	return !equal(segment);
}



bool SegmentLine::equal(SegmentLine & segment)
{
	return (_orig.equal(segment._orig) && _dest.equal(segment._dest)) || (_orig.equal(segment._dest) && _dest.equal(segment._orig));
}

Point SegmentLine::getPoint(double t)
{
	return Point(this->_orig.add((this->_dest.minus(this->_orig)).PointXScalar(t)));
}


bool SegmentLine::impSegmentIntersection(SegmentLine& segment)
{
    Point a = this->_orig;
    Point b = this->_dest;
    Point c = segment._orig;
    Point d = segment._dest;

    if(a.colinearImp(b,c) || a.colinearImp(b,d) || c.colinearImp(d,a) || c.colinearImp(d,b)) {
        return true;
    }

    return ((a.left(b,c) ^ (a.left(b,d))) && (c.left(d,a) ^ c.left(d,b)));
}

bool SegmentLine::isHorizontal()
{

    if(this->_dest.getY() - this->_orig.getY() == 0) {
        return true;
    }

    return false;
}




bool SegmentLine::isVertical()
{
    if(this->_dest.getX() - this->_orig.getX() == 0) {
        return true;
    }

    return false;
}


double SegmentLine::slope()
{
    return this->_orig.slope(this->_dest);
}

double SegmentLine::getEquC() {
    return this->_orig.getY() - (slope()*this->_orig.getX());
}

bool SegmentLine::segmentIntersection(SegmentLine &l) {

    Point a = this->_orig;
    Point b = this->_dest;
    Point c = l._orig;
    Point d = l._dest;

    if(a.colinear(c,d) || b.colinear(c,d) || c.colinear(a,b) || d.colinear(a,b)){
        return false;
    }else{
        return (a.left(c,d) ^ b.left(c,d)) && (c.left(a,b) ^ d.left(a,b));
    }

}


 // PROTECTED METHODS



void SegmentLine::out()
{
	std::cout << "Point A: )";
	_orig.out();
	std::cout << "Point B: ";
	_dest.out();
}



