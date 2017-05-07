/*
 * Copyright (c) 2011 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Vector2D.h
 * @date 02.06.2011
 * @author Michael Lipp
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <cmath>
#include "geometrylib/Point2D.h"

namespace GeometryLib {

/**
 * This class describes a vector in the two dimensional space. A vector
 * denotes the difference between two Points2D<T>.
 */
template <class T>
class Vector2D {
private:
	Point2D<T> endPos;

public:
	/**
	 * Create a new vector that denotes the difference between the
	 * given points.
	 */
	Vector2D(Point2D<T> start, Point2D<T> end)
		: endPos (end.x() - start.x(), end.y() - start.y()) {
	}

	virtual ~Vector2D() {
	}

	/**
	 * Return the difference on the x-axis denoted by this vector.
	 *
	 * @return the difference
	 */
	double dx() const {
		return endPos.x();
	}

	/**
	 * Return the difference on the y-axis denoted by this vector.
	 *
	 * @return the difference
	 */
	double dy() const {
		return endPos.y();
	}

	/**
	 * Return the square of the vector's length.
	 *
	 * @return the square of the length
	 */
	double squaredLength() const {
		double dx = endPos.x();
		double dy = endPos.y();
		return dx*dx + dy*dy;
	}

	/**
	 * Return the vector's length.
	 *
	 * @return the length
	 */
	double length() const {
		return sqrt(squaredLength());
	}

	/**
	 * Return the vector by the given angle and return the result.
	 *
	 * @param angle the angle
	 * @return the rotated vector
	 */
	Vector2D<T> rotate(double angle) const {
		return Vector2D<T>(Point2D<T>(0, 0), Point2D<T>
			(endPos.x() * std::cos(angle) - endPos.y() * std::sin(angle),
		     endPos.x() * std::sin(angle) + endPos.y() * std::cos(angle)));
	}

	/**
	 * Add this vector and the given vector and return the result.
	 *
	 * @param vec the vecor to add
	 * @return the result
	 */
	Vector2D<T> operator+ (const Vector2D<T>& vec) const {
		return Vector2D<T>(Point2D<T>(0,0), Point2D<T>
			(endPos.x() + vec.dx(),
			 endPos.y() + vec.dy()));
	}

	/**
	 * Scale the length of this vector to the given value.
	 *
	 * @param length the length of the new vector
	 * @return the scaled vector
	 */
	Vector2D<T> scale(double length) const {
		double scale = length / this->length();
		return Vector2D<T>(Point2D<T>(0,0), Point2D<T>
			(scale * endPos.x(), scale * endPos.y()));
	}

	/**
	 * Return the scalar product between this vector and another vector.
	 *
	 * @return the scalar product
	 */
	double operator* (const Vector2D<T>& vec) const  {
		return endPos.x() * vec.endPos.x()
			   + endPos.y() * vec.endPos.y();
	}

	/**
	 * Multiply the vector by the given scalar.
	 *
	 * @return the result
	 */
	Vector2D<T> operator* (T factor) const  {
		return Vector2D<T>(Point2D<T>(0,0), Point2D<T>
			(factor * endPos.x(), factor * endPos.y()));
	}

};

}

#endif /* RAY2D_H_ */
