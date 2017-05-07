/*
 * Copyright (c) 2011 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Segment2D.h
 * @date 02.06.2011
 * @author Michael Lipp
 */

#ifndef SEGMENT2D_H_
#define SEGMENT2D_H_

#include <cmath>
#include "geometrylib/Point2D.h"

namespace GeometryLib {

/**
 * This class describes a directed line between two points
 * in the two dimensional space.
 */
template <class T>
class Segment2D {
private:
	Point2D<T> startPos;
	Point2D<T> endPos;

	/**
	 * Find the intersection between this line and the given line,
	 * assuming endless lines.
	 *
	 * @param res the intersection point
	 * @param other the other line
	 * @return true if the lines intersect
	 */
	bool intersectionPoint (Point2D<T>& res, Segment2D<T> other) const {
		// Taken and adapted from
		// http://workshop.evolutionzone.com/2007/09/10/code-2d-line-intersection/

		// calculate differences
		Vector2D<T> v1(startPos, endPos);
		Vector2D<T> v2(other.startPos, other.endPos);

		// calculate the lengths of the two lines
		T len1=v1.length();
		T len2=v2.length();

		// calculate cosine of angle between the two lines.
		double ca=v1*v2/(len1 * len2);

		// if abs(angle)==1 then the lines are parallell,
		// so no intersection is possible
		if(std::abs(ca)==1) {
			return false;
		}

		// find intersection Pt between two lines
		Vector2D<T> v3(other.startPos, startPos);
		T div=v2.dy()*v1.dx()-v2.dx()*v1.dy();
		T ua=(v2.dx()*v3.dy()-v2.dy()*v3.dx())/div;
		res = startPos + v1 * ua;

		// return the valid intersection
		return true;
	}

public:
	/**
	 * Create a new segment from the start point to the end point.
	 *
	 * @param start the start point
	 * @param end the end point
	 */
	Segment2D(Point2D<T> start, Point2D<T> end)
		: startPos(start), endPos (end) {
	}

	virtual ~Segment2D() {
	}

	/**
	 * Return the start point of this segment.
	 *
	 * @return the start point
	 */
	Point2D<T> start() const {
		return startPos;
	}

	/**
	 * Return the end point of this segment.
	 *
	 * @return the end point
	 */
	Point2D<T> end() const {
		return endPos;
	}

	/**
	 * Return this segments's length.
	 *
	 * @return the length
	 */
	double length() const {
		return sqrt(squaredLength());
	}

	/**
	 * Return the square of this segments's length.
	 *
	 * @return the square of the length
	 */
	double squaredLength() const {
		double dx = endPos.x() - startPos.x();
		double dy = endPos.y() - startPos.y();
		return dx*dx + dy*dy;
	}

	/**
	 * Find the intersection between this line and the given line, if any.
	 *
	 * @param res the intersection point
	 * @param other the other line
	 * @return true if the lines intersect
	 */
	bool findIntersection (Point2D<T>& res, Segment2D<T> other) const {
		intersectionPoint(res, other);

		// if the lengths of the sets of segments is not the same as
		// the lengths of the line the point is actually
		// not on the line segment.

		// calculate the combined lengths of the two segments
		// between Pt-p1 and Pt-p2
		T segmentLen1 = Vector2D<T>(startPos, res).length()
					    + Vector2D<T>(res, endPos).length();
		if (abs(Vector2D<T>(startPos, endPos).length()-segmentLen1) > 0.001) {
			return false;
		}

		// calculate the combined lengths of the two segments
		// between Pt-p3 and Pt-p4
		T segmentLen2 = Vector2D<T>(other.startPos, res).length()
					    + Vector2D<T>(res, other.endPos).length();

		return abs(Vector2D<T>(other.startPos, other.endPos).length()
				   -segmentLen2) < 0.001;
	}

	/**
	 * Find the intersection between this line and the given ray, if any.
	 *
	 * @param res the intersection point
	 * @param ray the ray
	 * @return true if the line and the ray intersect
	 */
	bool findIntersection (Point2D<T>& res, Ray2D<T> ray) const {
		intersectionPoint(res, Segment2D<T>(ray.start(), ray.point(1)));

		// calculate the combined lengths of the two segments
		// between Pt-p1 and Pt-p2
		T segmentLen1 = Vector2D<T>(startPos, res).length()
					    + Vector2D<T>(res, endPos).length();

		// if the length of the combined segments istn't the length
		// of the line, the point is not on the line
		if(std::abs(Vector2D<T>(startPos, endPos).length()-segmentLen1) > 0.001) {
			return false;
		}

		// If a vector from ray's start to the intersection doesn't have
		// the same direction as the ray, the point is not on the ray.
		Vector2D<T> toRes = Vector2D<T>(ray.start(), res).scale(1);
		Vector2D<T> rayDir(ray.start(), ray.point(1));

		return std::abs(toRes.dx() - rayDir.dx()) < 0.001
			   && std::abs(toRes.dy() - rayDir.dy()) < 0.001;
	}

};

}

#endif /* SEGMENT2D_H_ */
