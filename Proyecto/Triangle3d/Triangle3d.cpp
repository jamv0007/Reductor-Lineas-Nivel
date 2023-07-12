
#include <iostream>
#include <cmath>
//#include "../BasicGeometry.h"
#include "Triangle3d.h"
#include "../Edge3d.h"


Triangle3d::Triangle3d()
{
}

Triangle3d::Triangle3d(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz)
	: _a(ax, ay, az), _b(bx, by, bz), _c(cx, cy, cz)
{
}

Triangle3d::Triangle3d(const Triangle3d & triangle)
	: _a(triangle._a), _b(triangle._b), _c(triangle._c)
{
}

Triangle3d::Triangle3d(Vect3d & va, Vect3d & vb, Vect3d & vc)
	: _a(va), _b(vb), _c(vc)
{
}

Triangle3d::~Triangle3d()
{
}

double Triangle3d::area()
{
    double area = BasicGeometry::determinant3x3(this->_a.getX(), this->_a.getY(), this->_a.getZ(), this->_b.getX(), this->_b.getY(), this->_b.getZ(),
                                  this->_c.getX(), this->_c.getY(), this->_c.getZ());
    area = area/2;
    
    return area;
        
}

Triangle3d::PointPosition Triangle3d::classify(Vect3d & point)
{
    Vect3d v(point.sub(this->_a));

    double len = v.module();

    if (BasicGeometry::equal(len, 0.0)){
        return PointPosition::COPLANAR;
    }

    v = v.scalarMul(1.0/len);
    Vect3d normal(this->normal());
    double d = v.dot(normal);

    if (d > BasicGeometry::EPSILON) {
        return PointPosition::POSITIVE;
    }else if (d < -BasicGeometry::EPSILON) {
        return PointPosition::NEGATIVE;

    }else{
        return PointPosition::COPLANAR;
    }

	return PointPosition::COPLANAR;
}



Vect3d Triangle3d::normal()
{
	Vect3d v1 (_b.sub(_a));
	Vect3d v2 (_c.sub(_a));
	Vect3d n (v1.xProduct(v2));
	double module = n.module();

	return (n.scalarMul(1.0f / module));
}

Triangle3d & Triangle3d::operator=(const Triangle3d & triangle)
{
	_a = triangle._a;
	_b = triangle._b;
	_c = triangle._c;

	return *this;
}

void Triangle3d::out()
{
	std::cout << "Triangle 3D: ";
	_a.out();
	_b.out();
	_c.out();
}



void Triangle3d::set(Vect3d & va, Vect3d & vb, Vect3d & vc)
{
	_a = va;
	_b = vb;
	_c = vc;
}

bool Triangle3d::rayTri(Ray3d &ray,Vect3d& p) {

    Vect3d edge1,edge2,h,s,q;
    Vect3d rayPoint(ray.getOrigin());

    float a,f,u,v;

    edge1 = this->_b.sub(_a);
    edge2 = this->_c.sub(_a);

    Vect3d rayVector(ray.getDestination().sub(rayPoint));

    h = rayVector.xProduct(edge2);

    a = edge1.dot(h);

    if(a > -BasicGeometry::EPSILON){
        return false;
    }

    f = 1.0/a;

    s = rayPoint.sub(this->_a);

    u = f * s.dot(h);

    if(u < 0.0 || u > 1.0){
        return false;
    }

    q = s.xProduct(edge1);

    v = f * rayVector.dot(q);

    if(v < 0.0 || u + v > 1.0){
        return false;
    }

    float t = f * edge2.dot(q);

    if(t > BasicGeometry::EPSILON){
        Vect3d rayT(rayVector.scalarMul(t));
        p.setVert(rayPoint.add(rayT).getX(),rayPoint.add(rayT).getY(),rayPoint.add(rayT).getZ());
        return true;
    } else{
        return false;
    }

    return false;
}

