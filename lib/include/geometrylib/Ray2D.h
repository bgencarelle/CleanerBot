/*
 * Copyright (c) 2011 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Ray2D.h
 * @date 02.06.2011
 * @author Michael Lipp
 */

#ifndef RAY2D_H_
#define RAY2D_H_

#include <cmath>
#include "geometrylib/Point2D.h"

namespace GeometryLib {

/**
 * This class defines a ray on a two dimensional plane
 * that starts at a given Point2D<T> and goes to infinity.
 *
 */
template <class T>
class Ray2D {
private:
	Point2D<T> startPos;
	Point2D<T> dirPos;
	Ray2D() {
	}

public:
	/**
	 * Create a new ray that starts at the given position and goes through
	 * the point given as second parameter.
	 *
	 * @param start the starting point
	 * @param dir a point this ray goes though
	 */
	Ray2D(Point2D<T> start, Point2D<T> dir) {
		startPos = start;
		double dx = dir.x() - start.x();
		double dy = dir.y() - start.y();
		double length = sqrt(dx*dx + dy*dy);
		dirPos = Point2D<T>(start.x() + dx/length, start.y() + dy/length);
	}

	/**
	 * Create a new ray that starts at the given position and has
	 * the given angle from the x-axis.
	 *
	 * @param start the starting point
	 * @param angle the agle from the x-axis
	 */
	Ray2D(Point2D<T> start, double angle) : startPos(0, 0), dirPos(1, 0) {
		startPos = start;
		dirPos = Point2D<T>(start.x() + cos(angle), start.y() + sin(angle));
	}

	virtual ~Ray2D() {
	}

	/**
	 * Rotate the ray by the given angle around its starting point and
	 * and return the result.
	 *
	 * @return the rotated vector
	 */
	Ray2D<T> rotate(double angle) const {
		double xShifted = dirPos.x() - startPos.x();
		double yShifted = dirPos.y() - startPos.y();
		Ray2D<T> res;
		res.startPos = startPos;
		res.dirPos = Point2D<T>
			(startPos.x() + xShifted * cos(angle) - yShifted * sin(angle),
		     startPos.y() + xShifted * sin(angle) + yShifted * cos(angle));
		return res;
	}

	/**
	 * Return the ray's starting point.
	 *
	 * @return the starting point
	 */
	Point2D<T> start() const {
		return startPos;
	}

	/**
	 * Return the point on the ray that has the given distance
	 * from the starting point.
	 *
	 * @param dist the distance from the starting point
	 */
	Point2D<T> point(double dist) const {
		return Point2D<T>(startPos.x() + dist * (dirPos.x() - startPos.x()),
						  startPos.y() + dist * (dirPos.y() - startPos.y()));
	}

};

}

#endif /* VECTOR2D_H_ */
