#include <iostream>
#include <string>
#include "../Polygon/PolygonGeo.h"
#include "Vertex.h"


Vertex::Vertex()
	: Point()
{
	_position = INVALID_POSITION;
	_polygon = nullptr;
}

Vertex::Vertex(const Point& point)
	: Point(point)
{
	_position = INVALID_POSITION;
	_polygon = nullptr;
}

Vertex::Vertex(const Point & point, PolygonGeo* polygon, int pos)
	: Point(point)
{
	_position = pos;
	_polygon = polygon;
}

Vertex::~Vertex()
{
}

bool Vertex::convex()
{
    Vertex plusOne = next();
    Vertex minusOne = previous();
    return (plusOne.left(minusOne,*this));
}

bool Vertex::concave()
{
    Vertex plusOne = next();
    Vertex minusOne = previous();
    return !(plusOne.left(minusOne,*this));
}


Vertex Vertex::next() {
    int nextPos = (_position + 1) % _polygon->getNumVertices();
    return _polygon->getVertexAt(nextPos);
}

Vertex Vertex::previous() {
    int previousPos = (_position - 1 + _polygon->getNumVertices()) % _polygon->getNumVertices();
    return _polygon->getVertexAt(previousPos);
}


SegmentLine Vertex::nextEdge()
{
    Point thisPoint = this->getPoint();
    Point nextPoint = next();
	return SegmentLine(thisPoint,nextPoint);
}

Vertex & Vertex::operator=(const Vertex & vertex)
{
	if (this != &vertex)
	{
		Point::operator=(vertex);
		this->_polygon = vertex._polygon;
		this->_position = vertex._position;
	}

	return *this;
}


SegmentLine Vertex::previousEdge()
{
    Point thisPoint = this->getPoint();
    Point previousPoint = previous();
    return SegmentLine(thisPoint,previousPoint);
}


void Vertex::out()
{
	Point::out();
	std::cout << "Position: " <<  std::to_string(_position);
}


