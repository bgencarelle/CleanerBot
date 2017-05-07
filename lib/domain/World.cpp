/*
 * Copyright (c) 2010 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file World.cpp
 * @date 17.09.2010
 * @author Michael Lipp
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include <ios>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <list>
#include <vector>
#include <limits>
#include "cleanerbot/World.h"

#ifdef max
#undef max
#endif

using namespace std;

World::World(string host, int port) {
	traceCommands = false;
	try {
		cmdCon = new SocketClient(host, port);
	} catch (string& e) {
		cerr << "Verbindung zum Anzeige-Server kann nicht hergestellt werden: "
			 << e << endl;
		cmdCon = NULL;
	}
	refCounter = new int(1);

	room = NULL;
	stringstream cmd;
	cmd << "SET NAME World@" << this;
	sendCommand(cmd);
}

World::World(const World& ref) {
	*ref.refCounter += 1;
	cmdCon = ref.cmdCon;
	refCounter = ref.refCounter;
	traceCommands = ref.traceCommands;

	room = new Room (*ref.room);
}

World::~World() {
	if (room != NULL) {
		delete room;
	}
	decRefCounter();
}

World& World::operator=	(const World& ref) {
	*ref.refCounter += 1;
	decRefCounter();
	cmdCon = ref.cmdCon;
	refCounter = ref.refCounter;
	traceCommands = ref.traceCommands;

	if (room != NULL) {
		delete room;
		room = new Room (*ref.room);
	}
	return *this;
}

void World::decRefCounter() {
	if (--(*refCounter) == 0) {
		sendCommand("CLOSE");
		delete cmdCon;
		cmdCon = NULL;
		delete refCounter;
		refCounter = NULL;
	}
}

bool World::getTraceCommands () {
	return traceCommands;
}

void World::setTraceCommands (bool trace) {
	traceCommands = trace;
}

int World::sendCommand(const string& cmd, string& rest) {
	if (cmdCon == NULL) {
		return 0;
	}
	if (traceCommands) {
		cerr << cmd << endl;
	}
	string s = cmd + "\r\n";
	if (cmdCon->SendBytes(s) < 0) {
		throw ios_base::failure("Verbindung zum Server verloren");
	}
	while (true) {
	    string response = cmdCon->ReceiveLine();
	    if (response.size() == 0) {
	    	throw ios_base::failure("Verbindung zum Server verloren");
	    }
	    size_t eol = response.find_first_of("\r\n");
	    if(eol >= 0) {
	        response = response.substr(0, eol);
	    }
	    if(traceCommands) {
	        cerr << response << endl;
	    }
	    if(response.size() > 4){
	        rest = response.substr(4);
	    } else {
	        rest = "";
	    }
	    int resCode = atoi(response.substr(0,3).c_str());
	    if (resCode / 100 != 1) {
	    	return resCode;
	    }
	}
}

int World::sendCommand(const string& cmd) {
	string s;
	return sendCommand(cmd, s);
}

int World::sendCommand(stringstream& cmd, string& rest) {
	int result = sendCommand(cmd.str(), rest);
	cmd.str("");
	cmd.clear();
	return result;
}

int World::sendCommand(stringstream& cmd) {
	string s;
	return sendCommand(cmd, s);
}

string World::getKey() {
	string s;
	int returnCode = sendCommand("GET KEY", s);
	if (returnCode / 100 == 2) {
		int last = s.length() - 1;
		while (s[last] != '"') {
			last -= 1;
		}
		return s.substr(1, last - 1);
	}
	return "";
}

void World::setRoom(const Room& newRoom) {
	room = new Room(newRoom);
	// Raster erzeugen
	sendCommand("START SCENE");
	// Wände senden
	list<Wall> walls = room->getWalls();
	for (list<Wall>::const_iterator wall = walls.begin();
		 wall != walls.end(); wall++) {
		list<Polygon2D> polies = wall->getShape();
		for (list<Polygon2D>::const_iterator
			 poly = polies.begin(); poly != polies.end(); poly++) {
			stringstream cmd;
			cmd << "WALL ";
			const vector<Point2D> vertices = poly->vertices();
			for (vector<Point2D>::const_iterator vi = vertices.begin();
				 vi != vertices.end(); vi++) {
				if (vi != vertices.begin()) {
					cmd << ";";
				}
				cmd << vi->x() << "," << vi->y();
			}
			sendCommand(cmd);
		}
	}
	// Alles anzeigen
	sendCommand("END SCENE");
}

double World::distToRoom (const Ray2D& ray) const {
	double dist = numeric_limits<double>::max();
	if (room == NULL) {
		return dist;
	}
	list<Wall> walls = room->getWalls();
	for (list<Wall>::const_iterator itr = walls.begin();
		 itr != walls.end(); itr++) {
		double d = itr->distance(ray);
		if (d < dist) {
			dist = d;
		}
	}
	return dist;
}

double World::distanceFront
	(double positionX, double positionY, double angle, double diameter) const {
	Ray2D position (Point2D(positionX, positionY), angle);
	return distToRoom(position) - diameter/2;
}

double World::distanceLeft
	(double positionX, double positionY, double angle, double diameter) const {
	Ray2D posLeft (Point2D(positionX, positionY), angle + M_PI/2);
	return distToRoom(posLeft) - diameter/2;
}

double World::distanceRight
	(double positionX, double positionY, double angle, double diameter) const {
	Ray2D posRight (Point2D(positionX, positionY), angle - M_PI/2);
	return distToRoom(posRight) - diameter/2;
}

void World::show
	(double positionX, double positionY, double angle, double diameter) {
	stringstream cmd;
	cmd << "VACUUM CLEANER "
		<< positionX << ","
		<< positionY << ";"
		<< cos(angle) << "," << sin(angle) << ";"
		<< diameter;
	sendCommand(cmd);
}

void World::showStatus (string statusText) {
	sendCommand("STATUSLINE " + statusText);
}
