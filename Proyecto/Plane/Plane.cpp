
#include <iostream>
#include "Plane.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
//#include "../BasicGeometry.h"


Plane::Plane(Vect3d & p, Vect3d & u, Vect3d & v, bool arePoints)
{
	if (!arePoints)			// Vectors: pi = p + u * lambda + v * mu 
	{			
		_a = p;
		_b = u.add(_a);
		_c = v.add(_a);
	}
	else 
	{						// 3 points in the plane.
		_a = p;
		_b = u;
		_c = v;
	}
}

Plane::Plane(const Plane & plane)
	: _a(plane._a), _b(plane._b), _c(plane._c)
{
}

Plane::~Plane()
{
}

bool Plane::coplanar(Vect3d & point)
{
    double suma = (this->getA() * point.getX()) + (this->getB() * point.getY()) + (this->getC() * point.getZ()) + this->getD();
    if(suma == 0){
        return true;
    }

	return false;
}

double Plane::distance(Vect3d & point)
{
    Vect3d n(this->getA(), this->getB(), this->getC());

    double landa = -1 * (n.dot(point) + this->getD());

    if(n.module() != 1){
        landa = landa / (n.dot(n));
    }

    return (n.scalarMul(landa)).module();
}    

double Plane::getA()
{
	//return (BasicGeometry::determinant2x2(_c.getZ() - _a.getZ(), _c.getY() - _a.getY(), _b.getY() - _a.getY(), _b.getZ() - _a.getZ()));
    Vect3d pq(this->_b.sub(_a));
    Vect3d pr(this->_c.sub(_a));

    Vect3d pqxpr(pq.xProduct(pr));

    return pqxpr.getX();

}

double Plane::getB()
{
	//return (BasicGeometry::determinant2x2(_c.getX() - _a.getX(), _c.getZ() - _a.getZ(), _b.getZ() - _a.getZ(), _b.getX() - _a.getX()));
    Vect3d pq(this->_b.sub(_a));
    Vect3d pr(this->_c.sub(_a));

    Vect3d pqxpr(pq.xProduct(pr));

    return pqxpr.getY();
}

double Plane::getC()
{
	//return (BasicGeometry::determinant2x2(_c.getY() - _a.getY(), _c.getX() - _a.getX(), _b.getX() - _a.getX(), _b.getY() - _a.getY()));
    Vect3d pq(this->_b.sub(_a));
    Vect3d pr(this->_c.sub(_a));

    Vect3d pqxpr(pq.xProduct(pr));

    return pqxpr.getZ();
}

double Plane::getAN()
{
    //return (BasicGeometry::determinant2x2(_c.getZ() - _a.getZ(), _c.getY() - _a.getY(), _b.getY() - _a.getY(), _b.getZ() - _a.getZ()));
    Vect3d pq(this->_b.sub(_a));
    Vect3d pr(this->_c.sub(_a));

    Vect3d pqxpr(pq.xProduct(pr));

    double module = pqxpr.module();
    Vect3d nor(pqxpr.getX()/module,pqxpr.getY()/module,pqxpr.getZ()/module);

    return nor.getX();

}

double Plane::getBN()
{
    //return (BasicGeometry::determinant2x2(_c.getX() - _a.getX(), _c.getZ() - _a.getZ(), _b.getZ() - _a.getZ(), _b.getX() - _a.getX()));
    Vect3d pq(this->_b.sub(_a));
    Vect3d pr(this->_c.sub(_a));

    Vect3d pqxpr(pq.xProduct(pr));

    double module = pqxpr.module();
    Vect3d nor(pqxpr.getX()/module,pqxpr.getY()/module,pqxpr.getZ()/module);

    return nor.getY();
}

double Plane::getCN()
{
    //return (BasicGeometry::determinant2x2(_c.getY() - _a.getY(), _c.getX() - _a.getX(), _b.getX() - _a.getX(), _b.getY() - _a.getY()));
    Vect3d pq(this->_b.sub(_a));
    Vect3d pr(this->_c.sub(_a));

    Vect3d pqxpr(pq.xProduct(pr));

    double module = pqxpr.module();
    Vect3d nor(pqxpr.getX()/module,pqxpr.getY()/module,pqxpr.getZ()/module);

    return nor.getZ();
}

Vect3d Plane::getNormal()
{
    return Vect3d(getA(),getB(),getC());
}


bool Plane::intersect(Plane & plane, Line3d & line)
{


    //Se calcula producto cruzado de las normales que es la linea
    Vect3d n1(this->getNormal());
    Vect3d n2(plane.getNormal());

    Vect3d n3(n1.xProduct(n2));

    //Si es 0 son paralelos
    if(n3.getX() == 0 && n3.getY() == 0 && n3.getZ() ==0){
        return false;
    }

    //Se despeja z e y en la formula del plano con x = 0, se calcula z y se sustituye en y
    float a1 = round((-1.0*plane.getD()) * this->getB());
    float a = a1 + round((plane.getB() * this->getD()));
    float b = ((-1* plane.getB() * this->getC()) + (this->getB() * plane.getC()));
    double z =  a/b ;
    double y = (-this->getD() - this->getC() * z)/ this->getB();

    //se calcula el p1 como la suma del punto mas el vector normal del producto cruzado
    Vect3d p0(0,y,z);
    Vect3d p1(p0.add(n3));
    line.setLine(p0,p1);

    return true;

    /*std::cout<< this->getA() <<"x + "<< this->getB()<<"y +"<< this->getC()<<"z + "<< this->getD()<<std::endl;
    std::cout<< plane.getA() <<"x + "<< plane.getB()<<"y +"<< plane.getC()<<"z + "<< plane.getD()<<std::endl;

    Vect3d n1(this->getNormal());
    Vect3d n2(plane.getNormal());

    Vect3d n3(n1.xProduct(n2));

    int a1 = this->getA();
    int b1 = this->getB();
    int c1 = this->getC();
    int d1 = this->getD();

    int a2 = plane.getA();
    int b2 = plane.getB();
    int c2 = plane.getC();
    int d2 = plane.getD();

    int a3 = n3.getX();
    int b3 = n3.getY();
    int c3 = n3.getZ();

    int det = BasicGeometry::determinant3x3(a1,a2,a3,b1,b2,b3,c1,c2,c3);

    if(det == 0){
        return false;
    }

    float one = BasicGeometry::determinant2x2(b1,c1,b3,c3);
    float two = BasicGeometry::determinant2x2(b2,c2,b3,c3);
    float three = BasicGeometry::determinant2x2(a3,c3,a1,c1);
    float four = BasicGeometry::determinant2x2(a3,c3,a2,c2);
    float five = BasicGeometry::determinant2x2(a1,b1,a3,b3);
    float six = BasicGeometry::determinant2x2(a2,b2,a3,b3);

    float x0 = d2 * one - d1 * two / det;
    float y0 = d2 * three - d1 * four / det;
    float z0 = d2 * five - d1 * six / det;

    Vect3d p0(x0,y0,z0);
    Vect3d p1(p0.add(n3));

    line.setLine(p0,p1);

    return true;*/

}

bool Plane::intersect(Line3d & line, Vect3d & point)
{

    Vect3d a(line.getOrigin());
    Vect3d b(line.getDestination());

    Vect3d ab(b.sub(a));
    Vect3d n(this->getA(), this->getB(), this->getC());

    if(n.dot(ab) == 0){
        return false;
    }

    double landa = -1 * (n.dot(a) + this->getD());

    if(n.module() != 1 && ab.module() != 1){
        landa = landa / (n.dot(ab));
    }

    Vect3d lab(ab.scalarMul(landa));
    Vect3d p(a.add(lab));
    point.setVert(p.getX(),p.getY(),p.getZ());

    return true;
}

bool Plane::intersect(Plane& pa, Plane& pb, Vect3d& pinter){

    double det = BasicGeometry::determinant3x3(this->getA(), this->getB(), this->getC(), pa.getA(),pa.getB(),pa.getC(), pb.getA(),pb.getB(),pb.getC());

    if(det == 0){
        return false;
    }

    double xDet = BasicGeometry::determinant3x3(this->getD(), this->getB(), this->getC(), pa.getD(),pa.getB(),pa.getC(), pb.getD(),pb.getB(),pb.getC());
    double yDet = BasicGeometry::determinant3x3(this->getA(), this->getD(), this->getC(), pa.getA(),pa.getD(),pa.getC(), pb.getA(),pb.getD(),pb.getC());
    double zDet = BasicGeometry::determinant3x3(this->getA(), this->getB(), this->getD(), pa.getA(),pa.getB(),pa.getD(), pb.getA(),pb.getB(),pb.getD());

    double x = -1 * (xDet / det);
    double y = -1 * (yDet / det);
    double z = -1 * (zDet / det);

    pinter.setVert(x,y,z);

    return true;

}

Plane & Plane::operator=(const Plane & plane)
{
	if (this != &plane)
	{
		_a = plane._a;
		_b = plane._b;
		_c = plane._c;
	}

	return *this;
}

void Plane::out()
{
	std::cout << "Plane->a: ";
	_a.out();
	std::cout <<"Plane->b: ";
	_b.out();
	std::cout <<"Plane->c: ";
	_c.out();
}

Vect3d Plane::getP() {
    return this->_a;
}

Vect3d Plane::getQ() {
    return this->_b;
}

Vect3d Plane::getR() {
    return this->_c;
}

Vect3d Plane::projectPoint(Vect3d &v) {

    Vect3d n(getA(),getB(),getC());

    double r = (v.dot(n) + this->getD()) / n.module();

    Vect3d rn((n.scalarMul(r)));

    Vect3d rnn(rn.getX() / n.module(),rn.getY() / n.module(), rn.getZ() / n.module());

    Vect3d sol(v.sub(rnn));


    return sol;

}

Vect3d Plane::pPoint(Vect3d &v) {

    Vect3d n(getA(),getB(),getC());

    double r = (v.dot(n) + this->getD()) / n.module();

    Vect3d rn((n.scalarMul(r)));

    Vect3d rnn(rn.getX() / n.module(),rn.getY() / n.module(), rn.getZ() / n.module());

    Vect3d sol(v.sub(rnn));


    return sol;
}

PointCloud3d Plane::projectCloud(PointCloud3d &pc) {

    PointCloud3d newPCloud;

    for(int i = 0; i < pc.size(); i++){
       Vect3d p(pc.getPoint(i));

       Vect3d n(pPoint(p));

       newPCloud.addPoint(n);


    }

    return newPCloud;
}