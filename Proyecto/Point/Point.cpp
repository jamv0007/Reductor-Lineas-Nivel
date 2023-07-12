#include <cmath>
#include <iostream>
#include <string>
#include "Point.h"


using namespace std;

Point::Point()
{
	_x = DEFAULT_VALUE;
	_y = DEFAULT_VALUE;
}

Point::Point(double x, double y, bool polar)
{
	if (!polar)
	{
		_x = x;
		_y = y;
	} 
	else
	{
		_x = y * cos(x);
		_y = y * sin(x);
	}
}


Point::Point(const Point& point)
{
	_x = point._x;
	_y = point._y;
}

Point::~Point()
{
}

Point Point::minus(Point &b) {
    return Point(this->_x - b._x, this->_y - b._y);
}

Point Point::add(Point &b) {
    return Point(this->_x - b._x, this->_y - b._y);
}

Point::PointClassification Point::classify(Point & p0, Point & p1)
{

    Point p2(this->_x, this->_y);
    Point a = p1.minus(p0);
    Point b = p2.minus(p0);
    double sa = a._x * b._y - b._x * a._y;
    if (sa > 0.0) return PointClassification::LEFT;
    if (sa < 0.0) return PointClassification::RIGHT;
    if ((a._x*b._x < 0.0) || (a._y*b._y < 0.0)) return PointClassification::BACKWARD;
    if (a.getModule() < b.getModule()) return PointClassification::FORWARD;
    if (p0==p2) return PointClassification::ORIGIN;
    if (p1==p2) return PointClassification::DEST;

    return PointClassification::BETWEEN;
    

}

bool Point::colinear(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result != PointClassification::LEFT) && (result != PointClassification::RIGHT);
}

bool Point::colinearImp(Point &a, Point &b) {
    if(abs(triangleArea2(a,b)) > 0){
        return false;
    }else{
        if(abs(a._x - b._x) > 0){
            return (((a._x <= _x) && (_x <= b._x)) || ((a._x >= _x) && (_x >= b._x)));
        }else{
            return (((a._y <= _y) && (_y <= b._y)) || ((a._y >= _y) && (_y >= b._y)));
        }
    }

}

double Point::distPoint(Point & p)
{
	return std::sqrt(std::pow(p._x - _x, 2) + std::pow(p._y - _y, 2));
}

double Point::getAlpha()
{
    if(_x >= 0) {
        double angle = atan(_y / _x);
        return angle;
    }

    return 0;
}


double Point::getModule()
{
	return std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
}

bool Point::leftAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == PointClassification::LEFT) || (result != PointClassification::RIGHT);
}

Point & Point::operator=(const Point & point)
{
	_x = point._x;
	_y = point._y;

	return *this;
}

/*Point & Point::operator+(const Point & point)
{

    Point res(_x + point._x, _y + point._y);

    return res;
}

Point & Point::operator-(const Point & point)
{

    Point res(_x - point._x, _y - point._y);

    return res;
}*/

bool Point::operator==(const Point & point)
{

    if(_x == point._x && _y == point._y){
        return true;
    }

    return false;
}

Point &Point::PointXScalar(double t) {

    Point res(this->_x * t, this->_y * t);

    return res;
}

bool Point::rightAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == PointClassification::RIGHT) || (result != PointClassification::LEFT);
}

double Point::slope(Point & p)
{
    double slope = (p._y - this->_y) / (p._x - this->_x);
    return slope;
}

void Point::out()
{
    string outstring  =  "Coordinate x: " + std::to_string(_x) + ", coordinate y: " + std::to_string(_y) ;
    cout << outstring << endl;;
}

double Point::triangleArea2(Point &a, Point &b) {
    return BasicGeometry::determinant3x3(this->_x, this->_y,1,a._x,a._y,1,b._x,b._y,1);
}
