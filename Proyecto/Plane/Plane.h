
/* 
 * File:   Plane.h
 * Author: lidia
 *
 * Created on 26 de enero de 2021, 17:56
 */

#ifndef PLANE_H
#define PLANE_H


#include "../Line3d/Line3d.h"
#include "../Segment3d/Segment3d.h"
#include "../Vect3d/Vect3d.h"
#include "../Cloud3d/PointCloud3d.h"

/**
*	@brief This class a represents a 3D plane represented by three points.
*	@author Lidia Mª Ortega Alvarado.
*/
class Plane
{
public:
	enum IntersectionType 
	{
		POINT, SEGMENT, COPLANAR
	};

public:
	class IntersectionLine 
	{
		Vect3d _point;
		IntersectionType _type;
	};

protected:
	Vect3d _a, _b, _c;
    Vect3d pPoint(Vect3d& v);

public:
	/**
	*
	*	@param p in pi = p + u * lambda + v * mu -> r from the points (R, S, T).
	*	@param u in pi = p + u * lambda + v * mu -> d from the points (R, S, T).
	*	@param v in pi = p + u * lambda + v * mu -> t from the points (R, S, T).
	*	@param If arePoints is false, then params are p + u * lambda + v * mu, otherwise are points (R, S, T).
	*/
	Plane(Vect3d& p, Vect3d& u, Vect3d& v, bool arePoints);

	/**
	*	@brief Copy constructor.
	*/
	Plane(const Plane& plane);

	/**
	*	@brief Destructor.
	*/
	virtual ~Plane();

	/**
	*	@brief Returns true if p is in the plane.
	*/	
	bool coplanar(Vect3d& point);

	/**
	*	@brief Distance between the plane and the point.
	*/
	double distance(Vect3d& point);

	/**
	*	@brief Returns A in AX + BY + CZ + D = 0.
	*/
	double getA();

	/**
	*	@brief Returns B in AX + BY + CZ + D = 0.
	*/
	double getB();

	/**
	*	@brief Returns C in AX + BY + CZ + D = 0.
	*/
	double getC();

    double getAN();
    double getBN();
    double getCN();
	/**
	*	@return D in AX + BY + CZ + D = 0.
	*/
	double getD() {
        //return (-1.0) * (getA() * _a.getX() + getB() * _a.getY() + getC() * _a.getZ());

        Vect3d pq(this->_b.sub(_a));
        Vect3d pr(this->_c.sub(_a));

        Vect3d pqxpr(pq.xProduct(pr));

        Vect3d inv(_a.scalarMul(-1));
        double d = pqxpr.dot(inv);

        return d;



    }



	/**
	*	@brief Returns the normal vector of (A, B, C) in Ax + By + Cz + D = 0.
	*/
	Vect3d getNormal();

        /**
	*	@brief Calculates the intersection point of a line and this plane, if exists.
	*/
	bool intersect(Line3d& line, Vect3d& point);
        
        /**
	*	@brief Calculates the intersection point of three planes.
	*/
	bool intersect(Plane& pa, Plane& pb, Vect3d& pinter);
        
	/**
	*	@brief Calculates the intersection line of a plane with this plane.
	*/
	bool intersect(Plane& plane, Line3d& line);

	
	/**
	*	@brief Assignment operator.
	*/
	virtual Plane& operator=(const Plane& plane);

	/**
	*	@brief Shows the plane values at the debug window.
	*/
	virtual void out();

    Vect3d getP();
    Vect3d getQ();
    Vect3d getR();

    Vect3d projectPoint(Vect3d& v);
    PointCloud3d projectCloud(PointCloud3d& pc);

};



#endif /* PLANE_H */

