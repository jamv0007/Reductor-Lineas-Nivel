
/* 
 * File:   AABB.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:10
 */

#ifndef AABB_H
#define AABB_H

#include "../Vect3d/Vect3d.h"

class Triangle3d;

class AABB
{
    
friend class DrawAABB;    
protected:
	Vect3d _min, _max;								// Edge points of the cube.
    bool planeBoxOverlap(Vect3d& normal,Vect3d& v0);
    bool axisTest_X01(double a,double b, double fa, double fb, Vect3d& v0, Vect3d& v2);
    bool axisTest_X2(double a,double b, double fa, double fb, Vect3d& v0, Vect3d& v1);
    bool axisTest_Y02(double a,double b, double fa, double fb, Vect3d& v0, Vect3d& v2);
    bool axisTest_Y1(double a,double b, double fa, double fb, Vect3d& v0, Vect3d& v1);
    bool axisTest_Z12(double a,double b, double fa, double fb, Vect3d& v1, Vect3d& v2);
    bool axisTest_Z0(double a,double b, double fa, double fb, Vect3d& v0, Vect3d& v1);
public:
	/**
	*	@brief Default constructor.
	*/
	AABB();

	/**
	*	@brief Constructor.
	*/
	AABB(Vect3d& min, Vect3d& max);

	/**
	*	@brief Copy constructor,
	*/
	AABB(const AABB& aabb);

	/**
	*	@brief Destructor.
	*/
	virtual ~AABB();

	

	
	/**
	*	@brief Returns the central point of the cube.
	*/
	Vect3d getCenter();

	/**
	*	@brief Returns the vector that goes from the center to the maximum point.
	*/
	Vect3d getExtent();

	/**
	*	@brief Returns the lowest corner of the cube.
	*/
	Vect3d getMin() { return _min; }

	/**
	*	@brief Returns the maximum points of the cube.
	*/
	Vect3d getMax() { return _max; }

	/**
	*	@brief Assignment operator.
	*/
	AABB& operator=(const AABB& orig);

	/**
	*	@brief Modifies the minimum point.
	*/
	void setMin(Vect3d& min) { _min = min; }

	/**
	*	@brief Modifies the maximum point.
	*/
	void setMax(Vect3d& max) { _max = max; }

    /***
     * @brief Interseccion triangulo aabb
     * @param tri triangulo
     * @return Si intersecta
     */
    bool aabbTri(Triangle3d tri);
};



#endif /* AABB_H */

