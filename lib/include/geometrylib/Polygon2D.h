/*
 * Copyright (c) 2011 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Polygon2D.h
 * @date 02.06.2011
 * @author Michael Lipp
 */

#ifndef POLYGON2D_H_
#define POLYGON2D_H_

#include <vector>
#include "geometrylib/Point2D.h"
#include "geometrylib/Segment2D.h"

namespace GeometryLib {

/**
 * This class models a polygon in the two dimensional space. The polygon
 * is defined by vertices of type Point2D<T>. The shape can be queried
 * by getting the vertices or the edges.
 */
template <class T>
class Polygon2D {
private:
	std::vector<Point2D<T> > points;

public:
	/**
	 * Initialize a new polygon with no points.
	 */
	Polygon2D() {
	}

	virtual ~Polygon2D() {
	}

	/**
	 * Add a point to the list of points that make the polygon's shape.
	 *
	 * @param point the point to add
	 */
	void add(const Point2D<T>& point) {
		points.push_back(point);
	}

	/**
	 * Retrieve a list of edges that make up the polygon's shape. The
	 * list starts with a line from the first point to the second point and
	 * ends with a line from the last point to the first point.
	 *
	 * @return the edges
	 */
	std::vector<Segment2D<T> > edges() const {
		std::vector<Segment2D<T> > res;
		if (points.size() < 2) {
			return res;
		}
		typename std::vector<Point2D<T> >::const_iterator iter = points.begin();
		Point2D<T> prev = *iter++;
		while (iter != points.end()) {
			res.push_back(Segment2D<T>(prev, *iter));
			prev = *iter++;
		}
		if (points.size() > 2) {
			res.push_back(Segment2D<T>(prev, *points.begin()));
		}
		return res;
	}

	/**
	 * Returns the list of points as added to the polygon.
	 *
	 * @return the list of points
	 */
	const std::vector<Point2D<T> > vertices() const {
		return points;
	}
};

}

#endif /* POLYGON2D_H_ */
