/*
 * Copyright (c) 2010 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Wall.cpp
 * @date 19.09.2010
 * @author Michael Lipp
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include "cleanerbot/Wall.h"

using namespace std;

Wall::Wall() {
}

Wall::Wall(const Polygon2D& shape) {
	addShape(shape);
}

Wall::Wall(const Point2D& end1, const Point2D& end2, double thickness) {
	addSection(end1, end2, thickness);
}

Wall::~Wall() {
}

void Wall::addShape (const Polygon2D& shape) {
	this->shape.push_back(shape);
}

void Wall::addSection (const Point2D& end1, const Point2D& end2,
		               double thickness) {
	Polygon2D poly; // Eventually, we want a polygon
    // Vector scaled to sqrt(2)*thickness/2
	Vector2D cornerOffset
		= Vector2D(end1, end2).scale(sqrt(thickness*thickness/2));
    // Rotate left 135 degrees
	poly.add(end1 + cornerOffset.rotate(3*M_PI/4));
	// Now right 135 degrees
	poly.add(end1 + cornerOffset.rotate(-3*M_PI/4));

	// Same with other end
	poly.add(end2 + cornerOffset.rotate(-M_PI/4));
	poly.add(end2 + cornerOffset.rotate(M_PI/4));

	// Add result to shapes
	addShape(poly);
}

std::list<Polygon2D> Wall::getShape() const {
	return shape;
}

double Wall::distance (const Ray2D& ray) const {
	double dist = std::numeric_limits<double>::max();
	for (std::list<Polygon2D>::const_iterator itr = shape.begin();
		 itr != shape.end(); itr++) {
		vector<Segment2D> edges = itr->edges();
		for (vector<Segment2D>::iterator ei = edges.begin();
			 ei != edges.end(); ei++) {
			Point2D res(0,0);
			if (ei->findIntersection(res, ray)) {
				double d = Vector2D(ray.start(), res).length();
				if (d < dist) {
					dist = d;
			    }
			}
		}
	}
	return dist;
}

