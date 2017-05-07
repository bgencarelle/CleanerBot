/*
 * Copyright (c) 2010 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Wall.h
 * @date 19.09.2010
 * @author Michael Lipp
 */

#ifndef WALL_H_
#define WALL_H_

#include <list>
#include "cleanerbot/Boundary.h"

/**
 * Diese Klasse repräsentiert eine Wand (Mauer) eines Raumes.
 * Wände können generell beliebige Formen annehmen. Im einfachsten Fall
 * ist die Form einer Wand ein (langgezogenes) Reckteck. Dieser Typ
 * von Wand kann direkt mit dem Konstruktor
 * #Wall(const Point2D& end1,const Point2D& end2,double thickness)
 * erzeugt werden.
 */
class Wall: public Boundary {
private:
	std::list<Polygon2D> shape;

public:
	/**
	 * Erzeugt eine Wand ohne vorgegebene Form. Wird nur in Kombination
	 * mit nachfolgenden Aufrufen von #addShape oder #addSection verwendet.
	 */
	Wall();

	/**
	 * Erzeugt eine Wand mit der durch das Polygon vorgegebenen Form.
	 */
	Wall(const Polygon2D& shape);

	/**
	 * Erzeugt eine Wand von dem angegebenen Endpunkt <code>end1</code> bis
	 * zu dem angegebenen Endpunkt <code>end2</code> mit der angegebenen Dicke.
	 * Die Endpunkte
	 * durch die angegebenen Endpunkte beschriebene Linie wird dabei
	 * entsperechend der Dicke vergrößert.
	 *
	 * Beispiel: Der Aufruf <code>%Wall(Point2D(0, 0), Point2D(10, 0), 1)</code>
	 * erzeugt auf dem Koordinatensystem eine Wand (Mauer), deren Grundfläche
	 * durch das Rechteck mit den Eckpunkten (-0.5; -0,5), (-0.5; 0.5),
	 * (10.5; 0.5) und (10.5; -0.5) beschrieben wird.
	 *
	 */
	Wall(const Point2D& end1, const Point2D& end2, double thickness = 0.12);
	virtual ~Wall();

	/**
	 * Erweitert die Wand um die durch das Polygon beschriebene Grundfläche.
	 */
	void addShape (const Polygon2D& shape);

	/**
	 * Erweitert die Wand um das durch Endpunkte und Dicke beschriebene
	 * Rechteck. Siehe
	 * #Wall(const Point2D& end1,const Point2D& end2,double thickness).
	 */
	void addSection (const Point2D& end1, const Point2D& end2,
			         double thickness = 0.12);

	/**
	 * Liefert alle Polygone, die zusammen die Grundfläche der Wand bilden.
	 */
	std::list<Polygon2D> getShape() const;

	/**
	 * Berechnet die Entfernung vom Anfangspunkt des übergebenen Strahls
	 * bis zum ersten Schnittpunkt mit dieser Wand.
	 */
	double distance (const Ray2D& ray) const;
};

#endif /* WALL_H_ */
