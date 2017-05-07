/*
 * Copyright (c) 2010 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Room.cpp
 * @date 05.09.2010
 * @author Michael Lipp
 */

#include <iostream>
#include <limits>
#include <cmath>
#include <list>
#include "cleanerbot/Room.h"

Room::Room() {
}

Room::~Room() {
}

void Room::addWall (const Wall& wall) {
	walls.push_back(wall);
}

std::list<Wall> Room::getWalls() const {
	return walls;
}

double Room::distance (const Ray2D& ray) const {
	double minDist = std::numeric_limits<double>::max();
	for (std::list<Wall>::const_iterator itr = walls.begin();
		 itr != walls.end(); itr++) {
		double dist = itr->distance(ray);
		if (dist < minDist) {
			minDist = dist;
		}
	}
	return minDist;
}
