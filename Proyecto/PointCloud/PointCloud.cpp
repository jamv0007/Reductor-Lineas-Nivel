
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <random>
#include "PointCloud.h"


PointCloud::PointCloud()
{
}

PointCloud::PointCloud(int size, float max_x, float max_y)
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(-max_x,max_x);
    std::uniform_real_distribution<double> distr2(-max_y,max_y);

	for(int i = 0; i < size; i++){
        double valueX = distr(eng);
        double valueY = distr2(eng);
        Point n(valueX,valueY);
        addPoint(n);
    }

}

PointCloud::PointCloud(const std::string& filename)
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
            Point v(x,y);
            addPoint(v);
        }

    }else{
        throw std::runtime_error("PointCloud -> Fallo al abrir el archivo " + filename);
    }

    file.close();
}

PointCloud::~PointCloud()
{
}

void PointCloud::addPoint(Point& p)
{
	_points.push_back(p);
}

Point PointCloud::centralPoint()
{
    Point centralPoint(0,0);
    int pos = 0;
    double length = _points[pos].distPoint(centralPoint);
	for(int i = 1; i < _points.size(); i++){
        double nextElementLength =  _points[i].distPoint(centralPoint);
        if( nextElementLength < length){
            pos = i;
            length = nextElementLength;
        }
    }

    return _points[pos];

}

void PointCloud::deletePoint(int index)
{
	if (index < _points.size())
	{
		_points.erase(_points.begin() + index);
	}
}



Point PointCloud::getPoint(int position)
{
	if ((position >= 0) && (position < _points.size())) 
	{
		return _points[position];
	}

	return Point();
}

PointCloud & PointCloud::operator=(const PointCloud& pointCloud)
{
	if (this != &pointCloud)
	{
		this->_points = pointCloud._points;
	}

	return *this;
}

void PointCloud::save(const std::string& filename)
{
    std::ofstream aux;

    aux.open(filename.c_str());
    if(!aux.good()){
        throw std::runtime_error("PointCloud -> Fallo a abrir el archivo " + filename);
    }else{
        std::string dat;
        for(int i = 0; i < _points.size(); i++){
            std::stringstream ss;

            if(i == _points.size()-1) {
                ss << _points[i].getX() << " " << _points[i].getY();
            }else {
                ss << _points[i].getX() << " " << _points[i].getY() << std::endl;
            }
            dat = ss.str();
            aux << dat;
        }

    }
    aux.close();
}