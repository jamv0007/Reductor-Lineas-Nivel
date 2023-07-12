
/* 
 * File:   Ray3d.h
 * Author: lidia
 *
 * Created on 26 de enero de 2021, 17:22
 */

#ifndef RAY3D_H
#define RAY3D_H

#include "../Edge3d.h"

/**
*	@brief This class represents a ray that goes from an origin to the infinite.
*	@author Lidia Mª Ortega Alvarado.
*/
class Ray3d : public Edge3d
{
protected:
	/**
	*	@brief Checks if the parametric value t is valid. It is only invalid if t is smaller than 0.
	*/
	virtual bool isTvalid(double t) { return (t >= 0); }

public:
	/**
	*	@brief Constructor.
	*/
	Ray3d(Vect3d& orig, Vect3d& dest);

	/**
	*	@brief Copy constructor.
	*/
	Ray3d(const Ray3d& ray);

	/**
	*	@brief Destructor.
	*/
	virtual ~Ray3d();

	/**
	*	@brief Assignment operator.
	*/
	virtual Ray3d& operator=(const Ray3d& ray);

	/**
	*	@brief Shows some information about the ray at the debug window.
	*/
	virtual void out();
};




#endif /* RAY3D_H */

