#include <cmath>
#include <inttypes.h>
#include <sstream>
#include <fstream>
#include <random>
#include <vector>
//#include "../BasicGeometry.h"
#include "PointCloud3d.h"
#include "DrawCloud3d.h"
#include "../Vect3d/DrawVect3d.h"
#include "../Line3d/DrawLine3d.h"
#include "../Segment3d/Segment3d.h"
#include "../Segment3d/DrawSegment3d.h"
#include "../RegularMesh3d/RegularMesh3d.h"
#include <iostream>

PointCloud3d::PointCloud3d(int n, int k) {

    int pointsForCluster = n / k;

    Vect3d min(-10,-10,-10);
    Vect3d max(10,10,10);

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(min.getX(),max.getX());
    std::uniform_real_distribution<double> distr2(min.getY(),max.getY());
    std::uniform_real_distribution<double> distr3(min.getZ(),max.getZ());

    std::random_device rd2;
    std::default_random_engine eng2(rd2());
    std::uniform_real_distribution<float> distr4(0,2.0f);
    std::uniform_real_distribution<float> distr5(0,M_PI);
    std::uniform_real_distribution<float> distr6(0,2*M_PI);

    for(int i = 0; i < k; i++){

        double x = distr(eng);
        double y = distr2(eng);
        double z = distr3(eng);

        Vect3d p(x,y,z);

        for(int j = 0; j < pointsForCluster; j++){
            float r = distr4(eng2);
            float theta = distr5(eng2);
            float pi = distr6(eng2);
            Vect3d v(p,r,theta,pi);

            _points.push_back(v);

        }


    }



    maxMin();

}

std::vector<std::string> PointCloud3d::split(std::string str, char pattern) {

    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<std::string> results;

    while(posFound >= 0){
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(splitted);
    }

    return results;
}

PointCloud3d::PointCloud3d(std::string file, bool plyColor) {

    std::ifstream f;
    std::string line;
    char empty = ' ';

    f.open(file,std::ios::in);

    int cont = 0;

    int stop = 0;
    if(plyColor){
        stop = 13;

    }else{
        stop = 10;
    }

    if(!f.fail()){
        while(!f.eof()){
            while(cont < stop) {
                std::getline(f, line);
                cont++;
            }

            std::getline(f, line);

            if(!line.empty()) {

                std::vector<std::string> res = split(line, empty);

                double x = std::stod(res[0]);
                double y = std::stod(res[1]);
                double z = std::stod(res[2]);
                Vect3d v(x, y, z);

                _points.push_back(v);
            }

        }

    }else{
        throw std::runtime_error("PointCloud3d -> Fallo al abrir el archivo " + file);
    }

    f.close();

    maxMin();
}

PointCloud3d::PointCloud3d() 
	: _maxPoint(INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) 
{
    maxMin();
}

PointCloud3d::PointCloud3d (std::vector<Vect3d>& pointCloud):_points(pointCloud),
        _maxPoint(INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY){
    maxMin();
}

PointCloud3d::PointCloud3d(const std::string & filename)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY)
{
	auto splitByComma = [this](std::string& string) -> std::vector<std::string>
	{
		std::stringstream ss(string);
		std::vector<std::string> result;

		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ',');
			result.push_back(substr);
		}

		return result;
	};

	std::string currentLine; 				// Línea actual del fichero.
	std::ifstream inputStream;				// Flujo de entrada.
	inputStream.open(filename.c_str());

	while (std::getline(inputStream, currentLine))
	{
		std::vector<std::string> coord = splitByComma(currentLine);

		if (coord.size() == 3)	
		{
			try {
				Vect3d point(std::stof(coord[0].c_str(), nullptr), std::stof(coord[1].c_str(), nullptr), (std::stof(coord[2].c_str(), nullptr)));
				this->addPoint(point);
			}
			catch (const std::exception& excep)
			{
				inputStream.close();

				throw excep;
			}
		}
	}
	inputStream.close();

    maxMin();// Cerramos fichero.
}

PointCloud3d::PointCloud3d(int size, float max_x, float max_y, float max_z)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY)
{
	_points = std::vector<Vect3d>();

	while (size > 0)
	{
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_x * 2.0f))) - max_x;
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_y * 2.0f))) - max_y;
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_z * 2.0f))) - max_z;
                Vect3d val (x,y,z);
		this->addPoint(val);

		--size;
	}


    maxMin();
}

PointCloud3d::PointCloud3d(int size, Vect3d min, Vect3d max)
        : _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY)
{
    _points = std::vector<Vect3d>();

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(min.getX(),max.getX());
    std::uniform_real_distribution<double> distr2(min.getY(),max.getY());
    std::uniform_real_distribution<double> distr3(min.getZ(),max.getZ());

    for(int i = 0; i < size; i++){
        double valueX = distr(eng);
        double valueY = distr2(eng);
        double valueZ = distr3(eng);
        Vect3d n(valueX,valueY,valueZ);
        addPoint(n);
    }


    maxMin();
}

PointCloud3d::PointCloud3d(int size, float radius)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY)
{
	_points = std::vector<Vect3d>();

	while (size > 0)
	{
		float theta = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)) * 2.0f * M_PI;
		float phi = std::acos(1.0f - 2.0f * static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)));
		double x = std::sin(phi) * std::cos(theta);
		double y = std::sin(phi) * std::sin(theta);
		double z = std::cos(phi);

		float r = radius * std::sqrt(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)));
		Vect3d point(r * x, r * y, r * z);
		this->addPoint(point);

		--size;
	}

    maxMin();
}

PointCloud3d::PointCloud3d(const PointCloud3d & pointCloud)
	: _points(pointCloud._points), _maxPoint(pointCloud._maxPoint), _minPoint(pointCloud._minPoint)
{
}

PointCloud3d::~PointCloud3d()
{

}

void PointCloud3d::addPoint(Vect3d & p)
{
	_points.push_back(p);
	this->updateMaxMin(_points.size() - 1);
}

AABB PointCloud3d::getAABB()
{
	return AABB(_minPoint, _maxPoint);
}



Vect3d PointCloud3d::getPoint(int pos)
{
	if ((pos >= 0) && (pos < _points.size())) {
		return _points[pos];
	}
	return Vect3d();
}

PointCloud3d& PointCloud3d::operator=(const PointCloud3d & pointCloud)
{
	if (this != &pointCloud)
	{
		_points = pointCloud._points;
		_maxPoint = pointCloud._maxPoint;
		_minPoint = pointCloud._minPoint;
	}

	return *this;
}

void PointCloud3d::save(const std::string & filename)
{
	std::ofstream file(filename);

	for (int i = 0; i < _points.size(); ++i)
	{
		file << _points[i].getX() << ", " << _points[i].getY() << ", " << _points[i].getZ() << std::endl;
	}

	file.close();
}


/// PROTECTED METHODS

void PointCloud3d::updateMaxMin(int index)
{
	Vect3d point = _points[index];

	if (point.getX() < _minPoint.getX()) { _minPoint.setX(point.getX()); _minPointIndex.setX(index); }
	if (point.getY() < _minPoint.getY()) { _minPoint.setY(point.getY()); _minPointIndex.setY(index); }
	if (point.getZ() < _minPoint.getZ()) { _minPoint.setZ(point.getZ()); _minPointIndex.setZ(index); }

	if (point.getX() > _maxPoint.getX()) { _maxPoint.setX(point.getX()); _maxPointIndex.setX(index); }
	if (point.getY() > _maxPoint.getY()) { _maxPoint.setY(point.getY()); _maxPointIndex.setY(index); }
	if (point.getZ() > _maxPoint.getZ()) { _maxPoint.setZ(point.getZ()); _maxPointIndex.setZ(index); }
}


void PointCloud3d::getMostDistanced (int &a, int &b){

    double max = 0;
    int first = 0;
    int second = 0;

    for(int i = 0; i < _points.size()-1; i++){
        for(int j = i + 1; j < _points.size(); j++){
            double current = _points[j].distance(_points[i]);
            //std::cout<<"actual: "<<current<<" Maxima: "<<max<<std::endl;
            if(current > max){
                max = current;
                first = j;
                second = i;
            }
        }
    }

    a = first;
    b = second;
}

void PointCloud3d::maxMin(){

    float minX = INFINITY;
    float minY = INFINITY;
    float minZ = INFINITY;

    float maxX = -INFINITY;
    float maxY = -INFINITY;
    float maxZ = -INFINITY;


    for(int i = 0; i < this->_points.size(); i++){
        if(this->_points[i].getX() < minX){
            minX = this->_points[i].getX();
        }
        if(this->_points[i].getY() < minY){
            minY = this->_points[i].getY();
        }
        if(this->_points[i].getZ() < minZ){
            minZ = this->_points[i].getZ();
        }
        if(this->_points[i].getX() > maxX){
            maxX = this->_points[i].getX();
        }
        if(this->_points[i].getY() > maxY){
            maxY = this->_points[i].getY();
        }
        if(this->_points[i].getZ() > maxZ){
            maxZ = this->_points[i].getZ();
        }
    }

    this->_minPoint.setVert(minX,minY,minZ);
    this->_maxPoint.setVert(maxX,maxY,maxZ);

}


std::vector<std::vector<Vect3d*>> PointCloud3d::kmeans_naive(int k) {



    //Lista de los centroides actuales
    std::vector<Vect3d> centriodes;


    srand(time(NULL));

    //Se generan los k centriodes de forma aleatoria dentro de la nube de puntos
    while(centriodes.size() < k){
        int  index = rand() % _points.size();
        bool is = false;
        for(int i = 0; i < centriodes.size() && !is; i++){
            if(_points[index] == centriodes[i]){
                is = true;
            }
        }

        if(!is){

            centriodes.push_back(_points[index]);
        }
    }

    std::map<int,int> p;
    std::vector<Vect3d> component;
    std::vector<int> number;
    std::vector<std::vector<Vect3d*>> cluster;

    for(int i = 0; i < k; i++){
        Vect3d v(0,0,0);
        component.push_back(v);
        number.push_back(0);
        std::vector<Vect3d*> newK;
        cluster.push_back(newK);
    }

    int it = 0;
    //Se crean los clusters y se llenan con los elementos cercanos
    inicializeClusters(k,centriodes,&p);

    bool change = false;
    while(!change){
        //Se calcula el nuevo centroide con la media
        for(int i = 0; i < _points.size(); i++){
            component[p[i]].setX(component[p[i]].getX() + _points[i].getX());
            component[p[i]].setY(component[p[i]].getY() + _points[i].getY());
            component[p[i]].setZ(component[p[i]].getZ() + _points[i].getZ());
            number[p[i]]+=1;
        }

        //Se hace la media y se cambian los centriodes
        for(int i = 0; i < k; i++){
            component[i].setX(component[i].getX()/number[i]);
            component[i].setY(component[i].getY()/number[i]);
            component[i].setZ(component[i].getZ()/number[i]);

            centriodes[i] = component[i];

            //Se restablecen los valores
            component[i].setX(0);
            component[i].setY(0);
            component[i].setZ(0);
            number[i] = 0;
        }



        //Se recorren recalculan los grupos
        if(!updateClusters(centriodes,&p)){
            change = true;
        }

        it++;

    }

    //Preparar para devolver
    for(int i = 0; i < _points.size(); i++){
        Vect3d* vec = new Vect3d(_points[i]);
        cluster[p[i]].push_back(vec);
    }

    std::cout<<"Numero de iteraciones: "<<it<<std::endl;

    return cluster;

}

void PointCloud3d::inicializeClusters(int k,std::vector<Vect3d> centroides, std::map<int,int>*clusters) {

    //Distancia de cada punto a un centroide
    for(int j = 0; j < _points.size(); j++) {
        Vect3d vec(_points[j]);
        double distance = INFINITY;
        int centroideCercano = -1;
        //Para cada centro se calcula la distancia
        for (int i=0; i < centroides.size(); i++) {
            Vect3d dis(centroides[i].sub(vec));
            if(dis.module() < distance){
                distance = dis.module();
                centroideCercano = i;
            }
        }
        (*clusters)[j] = centroideCercano;
    }
}

bool PointCloud3d::updateClusters(std::vector<Vect3d> centroides, std::map<int,int>* clusters) {

    bool change = false;
    //Se recalcula el centroide mas cercano al punto
    for(int i = 0; i < _points.size(); i++){
        Vect3d vec(_points[i]);
        double distance = INFINITY;
        int centroideCercano = -1;
        for(int j = 0; j < centroides.size(); j++){
            Vect3d dis(centroides[j].sub(vec));
            if(dis.module() < distance){
                distance = dis.module();
                centroideCercano = j;
            }
        }
        //Si cambia de debe hacer otra iteracion
        if((*clusters)[i] != centroideCercano){
            change = true;
            (*clusters)[i] = centroideCercano;
        }

    }

    return change;

}


std::vector<std::vector<Vect3d *>> PointCloud3d::kmeans_grid(int k) {


    //Se crea la malla regular
    RegularMesh3d* mesh = new RegularMesh3d(_minPoint.getX(),_maxPoint.getX()+1,
                       _minPoint.getY(),_maxPoint.getY()+1,
                       _minPoint.getZ(),_maxPoint.getZ()+1,10);

    for(int i = 0; i < _points.size(); i++){
        mesh->insertData(_points[i]);

    }

    //Una vez que la malla esta llena, se calculan los centroides
    std::vector<Box*> centroides = mesh->getCentriodes(k);

    std::vector<Vect3d> centroCubo;
    std::map<int,int> p;
    std::vector<Vect3d> component;
    std::vector<int> number;
    std::vector<std::vector<Vect3d*>> cluster;

    //Inicializa
    for(int i = 0; i < k; i++){
        Vect3d v(0,0,0);
        component.push_back(v);
        number.push_back(0);
        std::vector<Vect3d*> newK;
        cluster.push_back(newK);
    }

    for(Box* c: centroides){
        centroCubo.push_back(mesh->getBoxCenter(c->getX(),c->getY(),c->getZ()));
    }


    //inicializa
    inicializeClusters(k,centroCubo,&p);

    int it = 0;
    bool change = false;
    while(!change){
        //Se calcula el nuevo centroide con la media
        for(int i = 0; i < _points.size(); i++){
            component[p[i]].setX(component[p[i]].getX() + _points[i].getX());
            component[p[i]].setY(component[p[i]].getY() + _points[i].getY());
            component[p[i]].setZ(component[p[i]].getZ() + _points[i].getZ());
            number[p[i]]+=1;
        }

        //Se hace la media y se cambian los centriodes
        for(int i = 0; i < k; i++){
            component[i].setX(component[i].getX()/number[i]);
            component[i].setY(component[i].getY()/number[i]);
            component[i].setZ(component[i].getZ()/number[i]);

            centroCubo[i] = component[i];

            //Se restablecen los valores
            component[i].setX(0);
            component[i].setY(0);
            component[i].setZ(0);
            number[i] = 0;
        }



        //Se recorren recalculan los grupos
        if(!updateClusters(centroCubo,&p)){
            change = true;
        }

        it++;

    }

    //Preparar para devolver
    for(int i = 0; i < _points.size(); i++){
        Vect3d* vec = new Vect3d(_points[i]);
        cluster[p[i]].push_back(vec);
    }

    std::cout<<"Numero de iteraciones: "<<it<<std::endl;

    delete mesh;

    return cluster;
}
