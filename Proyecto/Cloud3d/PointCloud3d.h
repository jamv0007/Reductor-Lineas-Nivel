
/* 
 * File:   PontCloud3d.h
 * Author: lidia
 *
 * Created on 26 de enero de 2021, 17:36
 */

#ifndef PONTCLOUD3D_H
#define PONTCLOUD3D_H


#include <string>
#include "../AABB/AABB.h"
//#include "TriangleMesh.h"
#include "../Vect3d/Vect3d.h"
#include "../Line3d/Line3d.h"
#include "map"

/**
*	@brief This class represents a set of points distributed in the space.
*	@author Lidia Mª Ortega Alvarado.
*/
class PointCloud3d
{
protected:
	std::vector<Vect3d> _points;
	Vect3d _maxPoint, _minPoint;						// AABB.
	Vect3d _maxPointIndex, _minPointIndex;				// Indices of those vertices which have the boundary coordinates of the mesh.

	
protected:
	/**
	*	@brief Updates the new maximum and minimum points taking into account a new point.
	*/
	void updateMaxMin(int index);
    /***
     * @brief Crea para un k y unos centroide, un mapa con de indice del vertice e indice del cluster asociado
     */
    void inicializeClusters(int k,std::vector<Vect3d> centroides, std::map<int,int> *clusters);
    /***
     * @brief Actualiza los clusters
     * @param centroides Nuevos centroides
     * @param clusters mapa de vertice con el cluster
     * @return si ha habido algun cambio entre vertices
     */
    bool updateClusters(std::vector<Vect3d> centroides, std::map<int,int> *clusters);
    std::vector<std::string> split(std::string str, char pattern);
public:
	/**
	*	@brief Default constructor.
	*/
	PointCloud3d();

	/**
	*	@brief Loads the point cloud from a file.
	*/
	PointCloud3d(const std::string& filename);

        /**
	*	@brief Construct the point cloud from a vector of points
	*/
	PointCloud3d(std::vector<Vect3d>& pointCloud);
        
	/**
	*	@brief Constructor.
	*/
	PointCloud3d(int size, float max_x, float max_y, float max_z);

    /***
     * @brief Constructor a partir de un punto minimo y el máximo
     * @param size Tamaño
     * @param min Vector minimo
     * @param max Vector maximo
     */
    PointCloud3d(int size, Vect3d min, Vect3d max);

    /***
     * @brief Constructor de nube que crea una nube de n puntos dividida en k clusters
     * @param n numero de puntos
     * @param k Clusters
     */
    PointCloud3d(int n, int k);

    /***
     * @brief Constructor que carga datos de un fichero ply
     * @param file fichero
     * @param ply esto solo sirve para diferenciarlo del de un fichero normal da igual el valor
     */
    PointCloud3d(std::string file,bool plyColor);

	/**
	*	@brief Alternative constructor with an uniform sphere distribution.
	*/
	PointCloud3d(int size, float radius);

	/**
	*	@brief Copy constructor.
	*/
	PointCloud3d(const PointCloud3d& pointCloud);

	/**
	*	@brief Destructor.
	*/
	virtual ~PointCloud3d();

	/**
	*	@brief Adds a new point to the cloud.
	*/
	void addPoint(Vect3d& p);

	/**
	*	@brief Removes all the points.
	*/
	void clear() { _points.clear(); }

	/**
	*	@brief Deletes the data saved from the convex hull step by step process.
	*/
	//void forgetConvexHullData() { delete _convexHullData; _convexHullData = nullptr; }

	/**
	*	@brief Returns the bounding box that delimites the point cloud space.
	*/
	AABB getAABB();

	/**
	*	@brief Generates a complete convex hull.
	*/
	//TriangleMesh* getConvexHull();

	/**
	*	@brief Generates the next triangle from the current convex hull.
	*/
	//TriangleMesh* getConvexHullNextTriangle();

	/**
	*	@brief Returns a certain point.
	*/
	Vect3d getPoint(int pos);

	/**
	*	@brief Returns all the cloud points.
	*/
	std::vector<Vect3d> getPoints() { return _points; }

	/**
	*	@brief Assigment operator.
	*/
	virtual PointCloud3d& operator=(const PointCloud3d& pointCloud);

	/**
	*	@brief Saves the cloud points in a file.
	*/
	void save(const std::string& filename);

	/**
	*	@brief Returns the number of points that this cloud contains.
	*/
	int size() { return _points.size(); }
    
    /**
    *    @brief get the index of the most distanced points in the cloud.
    */
    
    void getMostDistanced (int &a, int &b);

    /**
     * @brief Set the max and min of aabb
     */
    void maxMin();

    /***
     * @brief Usa el algoritmo naive para calcular los k clusters
     * @return Vector de clusters con los puntos de cada cluster
     */
    std::vector<std::vector<Vect3d*>> kmeans_naive(int k);

    /***
     * @brief Usa una malla regular en 3d para calcular los k clusters
     * @return Vector de clusters con los puntos de cada cluster
     */
    std::vector<std::vector<Vect3d*>> kmeans_grid(int k);


};



#endif /* PONTCLOUD3D_H */

