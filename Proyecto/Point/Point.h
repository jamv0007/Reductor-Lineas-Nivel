#pragma once

#include <limits.h>
#include <cmath>
#include "../BasicGeometry.h"

/**
*	@brief This class represents a 2D structure. This will be also the skeleton for other 2D structures such as Vertex or Vector.
*	@author Lidia 
*/
class Point
{
protected:
	const static int DEFAULT_VALUE = INT_MAX;					// Value of X and Y coordinates for an incomplete Point.

public:
	enum PointClassification {
		LEFT, RIGHT, FORWARD, BACKWARD, BETWEEN, ORIGIN, DEST
	};

protected:
	double _x, _y;

public:
	/**
	*	@brief Default constructor. Coordinates are initialized with an invalid value.
	*/
	Point();

	/**
	*	@brief Constructor. Depending on the value of polar, x may be an angle (radians) and y the vector module.
	*/
	Point(double x, double y, bool polar = false);



	/**
	*	@brief Copy constructor.
	*/
	Point(const Point& point);

	/**
	*	@brief Destructor.
	*/
	virtual ~Point();

    //Point & operator+(const Point & point);
    //Point & operator-(const Point & point);
    bool operator==(const Point & point);

    Point & PointXScalar(double t);
    Point add(Point& b);
    Point minus(Point& b);

	/**
	*	@brief Checks the position of the point respect to other two points (a, b).
	*/
	bool backward(Point& a, Point& b) { return classify(a, b) == PointClassification::BACKWARD; }

	/**
	*	@brief Determines the relative position of a point (this) with respect to other two given as _a parameter (which can form a segment).
	*/
	PointClassification classify(Point& p0, Point& p1);

	/**
	*	@brief Checks if this point lies on the same line where a and b belong.
	*/
	bool colinear(Point& a, Point& b);

    bool colinearImp(Point& a, Point& b);

	/**
	*	@brief Distance between this point and another one.
	*/
	double distPoint(Point& p);

	/**
	*	@brief Checks if the coordinates of this point are different from the coordinates of a point p.
	*/
	bool distinct(Point& p) { return (abs(_x - p._x) > BasicGeometry::EPSILON || std::abs(_y - p._y) > BasicGeometry::EPSILON); }

	/**
	*	@brief Checks if the coordinates of this point are equal from the coordinates of a point p.
	*/
	bool equal(Point& pt) { return (BasicGeometry::equal(_x, pt._x) && BasicGeometry::equal(_y, pt._y)); }

	 /**
	 *	@brief Checks the position of the point respect to other two points (a, b).
	 */
	bool forward(Point& a, Point& b) { return classify(a, b) == PointClassification::FORWARD; }

	/**
	*	@brief Returns the coordinate X of the point.
	*/
	double getX() { return _x; }

	/**
	*	@brief Returns the coordinate Y of the point.
	*/
	double getY() { return _y; }

	/**
	*	@brief Angle of this point interpreted as a polar coordinate (radians).
	*/
	double getAlpha();

	/**
	*	@brief Module of _a 2D structure. This method is useful for child classes.
	*/
	double getModule();

	/**
	*	@brief Checks the position of the point respect to other two points (a, b).
	*/
	bool isBetween(Point& a, Point& b) { return classify(a, b) == PointClassification::BETWEEN; }

	/**
	*	@brief Checks the value of the coordinates. If the values are the DEFAULT, then the point is not valid.
	*/
	bool isValid() { return (_x != DEFAULT_VALUE) && (_y != DEFAULT_VALUE); }

	/**
	*	@brief Checks the position of the point respect to other two points (a, b).
	*/
	bool left(Point& a, Point& b) { return classify(a, b) == PointClassification::LEFT; }

	/**
	*	@brief Checks the position of the point respect to other two points (a, b).
	*/
	bool leftAbove(Point& a, Point& b);

	/**
	*	@brief Assignment operator (override).
	*/
	virtual Point& operator=(const Point& point);

	/**
	*	@brief Shows in the debug dialog some information about the point.
	*/
	void out();

	/**
	*	@brief Checks the position of the point respect to other two points (a, b).
	*/
	bool rightAbove(Point& a, Point& b);

	/**
	*	@brief Checks the position of the point respect to other two points (a, b).
	*/
	bool right(Point& a, Point& b) { return classify(a, b) == PointClassification::RIGHT; }

	/**
	*	@brief Modifies the coordinate values.
	*/
	void set(double x, double y) { this->_x = x; this->_y = y; }

	/**
	*	@brief Modifies the X coordinate.
	*/
	void setX(double x) { _x = x; }

	/**
	*	@brief Modifies the Y coordinate.
	*/
	void setY(double y) { _y = y; }

	/**
	*	@brief Returns the slope between this point and p.
	*/
	double slope(Point& p);

	/**
	*	@brief Calculates the double area of the triangle formed by (this, a, b).
	*/
	double triangleArea2(Point& a, Point& b);
};

