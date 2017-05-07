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
 * Diese Klasse repräsentiert einen Raum, in dem sich der Saugroboter bewegen
 * kann. Die Grenzen des Raums werden durch Wände repräsentiert. Initial
 * sind für den Raum keine Wände definiert (unendlich großer Raum). Die Wände
 * müssen durch Aufrufe der Methode #addWall zum Raum hinzugefügt werden.
 * Damit ist es möglich, Räume mit beliebigen Formen zu definieren.
 */
class Room: public Boundary {
private:
	std::list<Wall> walls;

public:
	/**
	 * Erzeugt einen neuen Raum ohne Wände.
	 */
	Room();
	virtual ~Room();

	/**
	 * Liefert eine Liste mit allen Wänden, die zu dem Raum mit
	 * #addWall hinzugefügt wurden.
	 */
	std::list<Wall> getWalls() const;

	/**
	 * Fügt eine Kopie des übergebenen Objekts von Typ Wall zu dem Raum
	 * hinzu.
	 */
	void addWall (const Wall& wall);

	/**
	 * Berechnet die Entfernung vom Anfangspunkt des übergebenen Strahls
	 * bis zum ersten Schnittpunkt mit einer Mauer des Raums.
	 */
	virtual double distance (const Ray2D& ray) const;
};

#endif /* ROOM_H_ */
