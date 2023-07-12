
/* 
 * File:   Vect3d.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:11
 */

#ifndef VECT3D_H
#define VECT3D_H


#include <limits.h>
#include <vector>
#include <cmath>
#include "../Vect2d/Vect2d.h"

class Triangle3d;

/**
*	@brief Base class for any structure which needs 3 coordinates (point, vector...).
*	@author Lidia Mª Ortega Alvarado.
*/
class Vect3d
{
protected:
	const static int DEFAULT_VALUE = INT_MAX;	// Value of X and Y coordinates for an incomplete vector.

	enum Axes { X, Y, Z };

private:
	double _value[3];

public:
	/**
	*	@brief Default constructor.
	*/
	Vect3d();

	/**
	*	@brief Constructor.
	*/
	Vect3d(double x, double y, double z);

    /***
     * Constructor a partir de coordenadas polares desde un punto
     * @param vec Punto de inicio
     * @param r radio
     * @param theta angulo en latitud
     * @param phi angulo en longitud
     */
    Vect3d(const Vect3d& vec, float r, float theta, float phi);

	/**
	*	@brief Copy constructor.
	*/
	Vect3d(const Vect3d& vector);

	/**
	*	@brief Destructor.
	*/
	virtual ~Vect3d();

	/**
	*	@brief Vector sum. a + b.
	*/
	Vect3d add(Vect3d& b);

	/**
	*	@brief Checks if a, b and this vector are on a same line.
	*/
	bool collinear(Vect3d& a, Vect3d& b);

	/**
	*	@brief Distance between points.
	*/
	double distance(Vect3d& p);

	/**
	*	@brief Dot product.
	*/
	double dot(Vect3d& v);

	/**
	*	@brief Returns the coordinates of this vector as an array.
	*/
	std::vector<double> getVert();

	/**
	*	@brief Returns a certain coordinate of the vector.
	*/
	double get(unsigned int index) { return _value[index]; }

	/**
	*	@brief Returns the X coordinate.
	*/
	double getX();

	/**
	*	@brief Returns the Y coordinate.
	*/
	double getY();

	/**
	*	@brief Returns the Z coordinate.
	*/
	double getZ();

	/**
	*	@brief Returns the module of the vector.
	*/
	double module();

	/**
	*	@brief Assignment operator.
	*/
	virtual Vect3d& operator=(const Vect3d& vector);

	/**
	*	@brief Checks if two vectors are equal.
	*/
	virtual bool operator==(const Vect3d& vector);

	/**
	*	@brief Checks if two vectors are distinct.
	*/
	virtual bool operator!=(const Vect3d& vector);

	/**
	*	@brief Multiplication of this vector by an scalar value.
	*/
	Vect3d scalarMul(double value);

	/**
	*	@brief Modifies the value of a certain coordinate.
	*/
	void set(unsigned int index, double value) { _value[index] = value; }

	/**
	*	@brief Modifies the X coordinate.
	*/
	void setX(double x);

	/**
	*	@brief Modifies the Y coordinate.
	*/
	void setY(double y);

	/**
	*	@brief Modifies the Z coordinate.
	*/
	void setZ(double z);

	/**
	*	@brief Modifies all the vector values.
	*/
	void setVert(double x, double y, double z);

	/**
	*	@brief Vector subtraction.
	*/
	Vect3d sub(Vect3d& b);

	/**
	*	@brief Vectorial product.
	*/
	Vect3d xProduct(Vect3d& b);

	/**
	*	@brief Shows some information of the vector at the debug window.
	*/
	virtual void out();

    double slope(Vect3d b);


};



#endif /* VECT3D_H */

