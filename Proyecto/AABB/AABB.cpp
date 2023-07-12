#include "AABB.h"
#include "../Triangle3d/Triangle3d.h"
#include "../Polygon/PolygonGeo.h"
#include <iostream>


AABB::AABB()
{
}

AABB::AABB(Vect3d & min, Vect3d & max)
	: _min(min), _max(max)
{
}

AABB::AABB(const AABB & aabb)
	: _min(aabb._min), _max(aabb._max)
{
}

AABB::~AABB()
{
}




Vect3d AABB::getCenter()
{
    Vect3d distance(this->_max.sub(this->_min));
    double zMed = (distance.getZ()) / 2;
    double yMed = (distance.getY()) / 2;
    double xMed = (distance.getX()) / 2;
    Vect3d medDistance(xMed,yMed,zMed);
	return Vect3d(this->_min.add(medDistance));
}

Vect3d AABB::getExtent()
{
    Vect3d center(getCenter());
	return Vect3d(this->_max.sub(center));
}

AABB & AABB::operator=(const AABB & orig)
{
	_min = orig._min;
	_max = orig._max;

	return *this;
}



bool AABB::aabbTri(Triangle3d tri) {

    Vect3d center(this->getCenter());
    Vect3d v0(tri.getA().sub(center));
    Vect3d v1(tri.getB().sub(center));
    Vect3d v2(tri.getC().sub(center));

    Vect3d e0(v1.sub(v0));
    Vect3d e1(v2.sub(v1));
    Vect3d e2(v0.sub(v2));

    double fex = fabsf((float)e0.getX());
    double fey = fabsf((float)e0.getY());
    double fez = fabsf((float)e0.getZ());

    if(!axisTest_X01(e0.getZ(),e0.getY(),fez,fey,v0,v2)){
        return false;
    }

    if(!axisTest_Y02(e0.getZ(),e0.getX(),fez,fex,v0,v2)){
        return false;
    }

    if(!axisTest_Z12(e0.getY(),e0.getX(),fey,fex,v1,v2)){
        return false;
    }

    fex = fabsf((float)e1.getX());
    fey = fabsf((float)e1.getY());
    fez = fabsf((float)e1.getZ());

    if(!axisTest_X01(e1.getZ(),e1.getY(),fez,fey,v0,v2)){
        return false;
    }

    if(!axisTest_Y02(e1.getZ(),e1.getX(),fez,fex,v0,v2)){
        return false;
    }

    if(!axisTest_Z0(e1.getY(),e1.getX(),fey,fex,v0,v1)){
        return false;
    }

    fex = fabsf((float)e2.getX());
    fey = fabsf((float)e2.getY());
    fez = fabsf((float)e2.getZ());

    if(!axisTest_X2(e2.getZ(),e2.getY(),fez,fey,v0,v1)){
        return false;
    }

    if(!axisTest_Y1(e2.getZ(),e2.getX(),fez,fex,v0,v1)){
        return false;
    }

    if(!axisTest_Z12(e2.getY(),e2.getX(),fey,fex,v1,v2)){
        return false;
    }

    double maxX = BasicGeometry::max3(v0.getX(),v1.getX(),v2.getX());
    double minX = BasicGeometry::min3(v0.getX(),v1.getX(),v2.getX());

    if(minX > this->getExtent().getX() || maxX < -getExtent().getX()){
        return false;
    }

    double maxY = BasicGeometry::max3(v0.getY(),v1.getY(),v2.getY());
    double minY = BasicGeometry::min3(v0.getY(),v1.getY(),v2.getY());

    if(minY > this->getExtent().getY() || maxY < -getExtent().getY()){
        return false;
    }

    double maxZ = BasicGeometry::max3(v0.getZ(),v1.getZ(),v2.getZ());
    double minZ = BasicGeometry::min3(v0.getZ(),v1.getZ(),v2.getZ());

    if(minZ > this->getExtent().getZ() || maxZ < -getExtent().getZ()){
        return false;
    }

    Vect3d normal(e0.xProduct(e1));

    if(!planeBoxOverlap(normal,v0)){
        return false;
    }

    return true;
}

bool AABB::planeBoxOverlap(Vect3d& normal,Vect3d& v0) {

    Vect3d vmin,vmax;

    for(int i = 0; i <= 2; i++){

        double v = v0.get(i);

        if(normal.get(i) > 0.0f){
            vmin.set(i, (-1*this->getExtent().get(i))-v);
            vmax.set(i, this->getExtent().get(i)-v);
        }else{
            vmin.set(i, this->getExtent().get(i)-v);
            vmax.set(i, (-1*this->getExtent().get(i))-v);
        }
    }

    if(normal.dot(vmin) > 0.0f){
        return false;
    }

    if(normal.dot(vmax) >= 0.0f){
        return true;
    }

    return false;
}

bool AABB::axisTest_X01(double a, double b, double fa, double fb, Vect3d& v0, Vect3d& v2) {
    double p0 = a * v0.getY() - b * v0.getZ();
    double p2 = a * v2.getY() - b * v2.getZ();

    double min;
    double max;

    if(p0 < p2){
        min = p0;
        max = p2;
    }else{
        min = p2;
        max = p0;
    }

    double rad = fa * this->getExtent().getY() + fb * this->getExtent().getZ();

    if(min > rad || max < -rad){
        return false;
    }

    return true;
}

bool AABB::axisTest_X2(double a, double b, double fa, double fb, Vect3d &v0, Vect3d &v1) {
    double p0 = a * v0.getY() - b * v0.getZ();
    double p1 = a * v1.getY() - b * v1.getZ();

    double min;
    double max;

    if(p0 < p1){
        min = p0;
        max = p1;
    }else{
        min = p1;
        max = p0;
    }

    double rad = fa * this->getExtent().getY() + fb * this->getExtent().getZ();

    if(min > rad || max < -rad){
        return false;
    }

    return true;
}

bool AABB::axisTest_Y02(double a, double b, double fa, double fb, Vect3d &v0, Vect3d &v2) {
    double p0 = -a * v0.getX() + b * v0.getZ();
    double p2 = -a * v2.getX() + b * v2.getZ();

    double min;
    double max;

    if(p0 < p2){
        min = p0;
        max = p2;
    }else{
        min = p2;
        max = p0;
    }

    double rad = fa * this->getExtent().getX() + fb * this->getExtent().getZ();

    if(min > rad || max < -rad){
        return false;
    }

    return true;
}

bool AABB::axisTest_Y1(double a, double b, double fa, double fb, Vect3d &v0, Vect3d &v1) {
    double p0 = -a * v0.getX() + b * v0.getZ();
    double p1 = -a * v1.getX() + b * v1.getZ();

    double min;
    double max;

    if(p0 < p1){
        min = p0;
        max = p1;
    }else{
        min = p1;
        max = p0;
    }

    double rad = fa * this->getExtent().getX() + fb * this->getExtent().getZ();

    if(min > rad || max < -rad){
        return false;
    }

    return true;
}

bool AABB::axisTest_Z12(double a, double b, double fa, double fb, Vect3d &v1, Vect3d &v2) {
    double p1 = a * v1.getX() - b * v1.getY();
    double p2 = a * v2.getX() - b * v2.getY();

    double min;
    double max;

    if(p2 < p1){
        min = p2;
        max = p1;
    }else{
        min = p1;
        max = p2;
    }

    double rad = fa * this->getExtent().getX() + fb * this->getExtent().getY();

    if(min > rad || max < -rad){
        return false;
    }

    return true;
}

bool AABB::axisTest_Z0(double a, double b, double fa, double fb, Vect3d &v0, Vect3d &v1) {
    double p0 = a * v0.getY() - b * v0.getZ();
    double p1 = a * v1.getY() - b * v1.getZ();

    double min;
    double max;

    if(p0 < p1){
        min = p0;
        max = p1;
    }else{
        min = p1;
        max = p0;
    }

    double rad = fa * this->getExtent().getX() + fb * this->getExtent().getY();

    if(min > rad || max < -rad){
        return false;
    }

    return true;
}

