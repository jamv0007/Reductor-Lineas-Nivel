
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include "PolygonGeo.h"


PolygonGeo::PolygonGeo()
{
}

PolygonGeo::PolygonGeo(const PolygonGeo& PolygonGeo)
{
	_vertices = std::vector<Vertex>(PolygonGeo._vertices);
}

PolygonGeo::PolygonGeo(std::vector<Vertex>& vertices)
{
	_vertices = std::vector<Vertex>(vertices);
}

SegmentLine PolygonGeo::getEdge(int i)
{
	return SegmentLine(getVertexAt(i), getVertexAt((i + 1) % _vertices.size()));
}

PolygonGeo::PolygonGeo(const std::string & filename)
{
    std::ifstream file;
    std::string line;
    char empty = ' ';

    file.open(filename,std::ios::in);

    if(!file.fail()){
        while(!file.eof()){
            std::getline(file,line);
            std::string data = "";
            double x = 0;
            double y = 0;
            for(int i = 0; i < line.length(); i++){
                if(line[i] != empty){
                    data = data + line[i];
                }else{
                    x = std::stod(data);
                    data = "";
                }
            }
            y = std::stod(data);
            Vertex v(Point(x,y));
            add(v);
        }

    }else{
        throw std::runtime_error("PolygonGeo -> Fallo al abrir el archivo " + filename);
    }

    file.close();
}

PolygonGeo::~PolygonGeo()
{
}

bool PolygonGeo::add(Vertex & vertex)
{
	int index = _vertices.size();

	//if (intersectsWithAnySegment(vertex)) return false;

	_vertices.push_back(vertex);
	_vertices[index].setPolygon(this);
	_vertices[index].setPosition(index);

	return true;
}

bool PolygonGeo::add(Point & point)
{
	Vertex vertex(point);

	return this->add(vertex);
}

Vertex PolygonGeo::getVertexAt(int pos)
{
	if (pos >= 0 && pos < _vertices.size()) 
	{
		return _vertices[pos];
	}
	else 
	{
		return Vertex();
	}
}

bool PolygonGeo::convex()
{
    int cont = 0;
	for(int i = 0; i < _vertices.size(); i++){
        if(_vertices[i].convex()){
            cont++;
        }else{
            return false;
        }
    }

    if(cont == _vertices.size()){
        return true;
    }

    return false;
}



Vertex PolygonGeo::next(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index + 1) % _vertices.size()];
	}

	return Vertex();
}

void PolygonGeo::out()
{
	for (int i = 0; i < _vertices.size(); i++) {
		_vertices[i].out();
	}
}

Vertex PolygonGeo::previous(int index)
{
	if (index >= 0 && index < _vertices.size())
	{
		return _vertices[(index - 1 + _vertices.size()) % _vertices.size()];
	}

	return Vertex();
}

PolygonGeo & PolygonGeo::operator=(const PolygonGeo &polygon)
{
	if (this != &polygon)
	{
		this->_vertices = polygon._vertices;
	}

	return *this;
}

bool PolygonGeo::pointInConvexPolygonGeo(Point& point)
{
    int cont = 0;

    for(int i = 0; i < _vertices.size(); i++){
        Point p2 = _vertices[i].next();
        if(point.left(_vertices[i],p2)){
            cont++;
        }else{
            return false;
        }
    }

    if(cont == _vertices.size()){
        return true;
    }

    return false;
}

void PolygonGeo::save(const std::string& filename)
{
    std::ofstream aux;

    aux.open(filename.c_str());
    if(!aux.good()){
        throw std::runtime_error("PotygonGeo -> Fallo a abrir el archivo " + filename);
    }else{
        std::string dat;
        for(int i = 0; i < _vertices.size(); i++){
            std::stringstream ss;
            if(i == _vertices.size()-1) {
                ss << _vertices[i].getPoint().getX() << " " << _vertices[i].getPoint().getY();
            }else {
                ss << _vertices[i].getPoint().getX() << " " << _vertices[i].getPoint().getY() << std::endl;
            }
            dat = ss.str();
            aux << dat;
        }

    }
    aux.close();
}

void PolygonGeo::set(Vertex& vertex, int pos)
{
	if (pos >= 0 && pos < _vertices.size()) {
		_vertices[pos] = vertex;
		vertex.setPolygon(this);
		vertex.setPosition(pos);
	}
}

bool PolygonGeo::intersects(Line &line, Vect2d &interseccion) {

    for(int i = 0; i < this->getNumVertices(); i++){
        SegmentLine s = this->getEdge(i);
        if(s.intersects(line,interseccion)){
            return true;
        }

    }

    return false;
}

bool PolygonGeo::intersects(SegmentLine &segment, Vect2d &interseccion) {
    for(int i = 0; i < this->getNumVertices(); i++){
        SegmentLine s = this->getEdge(i);
        if(s.intersects(segment,interseccion)){
            return true;
        }

    }

    return false;
}

bool PolygonGeo::intersects(RayLine &ray, Vect2d &interseccion) {
    for(int i = 0; i < this->getNumVertices(); i++){
        SegmentLine s = this->getEdge(i);
        if(s.intersects(ray,interseccion)){
            return true;
        }

    }

    return false;
}


