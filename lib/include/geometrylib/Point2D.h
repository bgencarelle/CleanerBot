/*
 * Copyright (c) 2011 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Point2D.h
 * @date 02.06.2011
 * @author Michael Lipp
 */

#ifndef POINT2D_H_
#define POINT2D_H_

namespace GeometryLib {

/**
 * This template class models a point in the two dimensional space
 * using the supplied data type for storing the coordinates.
 */
template <class T> class Vector2D;

template <class T>
class Point2D {
private:
	T xCoord;
	T yCoord;

public:
	/**
	 * Initialize a new point with the given coordinates.
	 *
	 * @param x the x-axis coordinate
	 * @param y the y-axis coordinate
	 */
	Point2D(T x, T y) {
		xCoord = x;
		yCoord = y;
	}

	virtual ~Point2D() {
	}

	/**
	 * Return the value of the x-axis coordinate.
	 *
	 * @return x-axis coordinate
	 */
	T x() const {
		return xCoord;
	}

	/**
	 * Return the value of the y-axis coordinate.
	 *
	 * @return y-axis coordinate
	 */
	T y() const {
		return yCoord;
	};

	/**
	 * Translate the point by the given vector.
	 *
	 * @return the point obtained by translating this point by the given vector
	 */
	Point2D<T> operator+ (const Vector2D<T>& vec) const {
		return Point2D<T>(xCoord + vec.dx(), yCoord + vec.dy());
	}

};

}

#endif /* POINT2D_H_ */
