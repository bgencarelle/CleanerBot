/*
 * Copyright (c) 2010 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Boundary.h
 * @date 05.09.2010
 * @author Michael Lipp
 */

#ifndef BOUNDARY_H_
#define BOUNDARY_H_

#include "Geometry.h"

/**
 * Diese Klasse ist die gemeinsame Basisklasse aller Klassen, die
 * Objekte beschreiben, die den Saugroboter in seiner Bewegung begrenzen.
 */
class Boundary {
public:
	Boundary();
	virtual ~Boundary();

	/**
	 * Bestimmt die Entfernung zwischen dem Ausgangspunkt eines Strahls und
	 * dem Schnittpunkt des Strahls mit diesem begrenzenden Objekt.
	 */
	virtual double distance (const Ray2D& ray) const = 0;
};

#endif /* BOUNDARY_H_ */
