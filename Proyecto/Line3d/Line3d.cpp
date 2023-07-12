#include <iostream>
#include "limits.h"
#include <cmath>
//#include "../BasicGeometry.h"
#include "Line3d.h"

Line3d::Line3d()
{
}

Line3d::Line3d(Vect3d & orig, Vect3d & dest)
	: Edge3d(orig, dest)
{
}

Line3d::Line3d(const Line3d & line)
	: Edge3d(line)
{
}

Line3d::~Line3d()
{
}


double Line3d::distance(Line3d & line)
{
    Vect3d a(this->_orig);
    Vect3d b(this->_dest);
    Vect3d c(line._orig);
    Vect3d d(line._dest);

    Vect3d ab(b.sub(a));
    Vect3d cd(d.sub(c));

    Vect3d abxcd(ab.xProduct(cd));
    Vect3d ac(c.sub(a));

    double distance;
    distance = (abs(ac.dot(abxcd))) / (abxcd.module());

    return distance;
}

Line3d Line3d::normalLine(Vect3d & point)
{
    Vect3d a(this->_orig);
    Vect3d b(this->_dest);

    Vect3d ab(b.sub(a));
    Vect3d ap(point.sub(a));

    double landa;

    landa = ab.dot(ap);

    if(ab.module() != 1){
        landa = landa / ab.dot(ab);
    }

    Vect3d landaAB(ab.scalarMul(landa));

    Vect3d aLandaAB(a.add(landaAB));

    Vect3d pALandaAB(point.sub(aLandaAB));

    Vect3d point2(point.add(pALandaAB));

    Line3d sol(point,point2);

    return sol;
}

double Line3d::distance(Vect3d& p){

    Vect3d a(this->_orig);
    Vect3d b(this->_dest);

    Vect3d ab(b.sub(a));
    Vect3d ap(p.sub(a));

    double landa;

    landa = ab.dot(ap);

    if(ab.module() != 1){
        landa = landa / ab.dot(ab);
    }

    Vect3d landaAB(ab.scalarMul(landa));
    double distance = (ap.sub(landaAB)).module();

    return distance;
}

Line3d & Line3d::operator=(const Line3d & line)
{
	if (this != &line)
	{
		Edge3d::operator=(line);
	}

	return *this;
}

void Line3d::out()
{
	std::cout << "Line->Origin: ";
	_orig.out();
	std::cout << "Line->Destination: ";
	_dest.out();
}

void Line3d::setLine(Vect3d a, Vect3d b) {
    this->_orig = a;
    this->_dest = b;
}

