/*
 * Copyright (c) 2010 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file Room.h
 * @date 05.09.2010
 * @author Michael Lipp
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <list>
#include "cleanerbot/Boundary.h"
#include "cleanerbot/Wall.h"

/**
 * Diese Klasse repr�sentiert einen Raum, in dem sich der Saugroboter bewegen
 * kann. Die Grenzen des Raums werden durch W�nde repr�sentiert. Initial
 * sind f�r den Raum keine W�nde definiert (unendlich gro�er Raum). Die W�nde
 * m�ssen durch Aufrufe der Methode #addWall zum Raum hinzugef�gt werden.
 * Damit ist es m�glich, R�ume mit beliebigen Formen zu definieren.
 */
class Room: public Boundary {
private:
	std::list<Wall> walls;

public:
	/**
	 * Erzeugt einen neuen Raum ohne W�nde.
	 */
	Room();
	virtual ~Room();

	/**
	 * Liefert eine Liste mit allen W�nden, die zu dem Raum mit
	 * #addWall hinzugef�gt wurden.
	 */
	std::list<Wall> getWalls() const;

	/**
	 * F�gt eine Kopie des �bergebenen Objekts von Typ Wall zu dem Raum
	 * hinzu.
	 */
	void addWall (const Wall& wall);

	/**
	 * Berechnet die Entfernung vom Anfangspunkt des �bergebenen Strahls
	 * bis zum ersten Schnittpunkt mit einer Mauer des Raums.
	 */
	virtual double distance (const Ray2D& ray) const;
};

#endif /* ROOM_H_ */
