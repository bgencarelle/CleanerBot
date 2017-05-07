/**
 * Diese Datei definiert die Welt, in der sich der Saugroboter bewegt.
 *
 * Copyright (c) 2010 Prof. Dr. Michael Lipp, Hochschule Darmstadt
 *
 * @file World.h
 * @date 17.09.2010
 * @author Michael Lipp
 *
 * @mainpage Dokumentation der C++-Klassen zur Saugroboter-Welt
 *
 * @section intro_sec Einf�hrung
 *
 * Die vorliegende Modellierung einer Welt f�r die Simulation eines
 * Saugroboters wird
 * in der Veranstaltung GIT des Fachbereichs EIT der Hochschule Darmstadt
 * verwendet. Ziel ist, eine �berschaubaren Welt (Dom�ne) bereitzustellen, mit
 * der die Sudierenden in den �bungen experimentieren k�nnen.
 *
 * Die vorliegende doxygen Dokumentation beschreibt alle Klassen der
 * Anwendungsdom�ne (d.h. der modellierten Welt).
 *
 * @section console_sec Die Konsole
 *
 * Die bereitgestellte Umgebung wird durch eine graphische Konsole erg�nzt.
 * Die Konsole ist aus technischen Gr�nden als unabh�ngiges Programm
 * realisiert und muss bzw. kann daher unabh�ngig gestartet
 * werden. Der Start erfolgt �ber "Java Web Start" ohne weitere
 * Installation durch Aufruf von
 * <a href="http://lipp.eit.h-da.de/cb/CleanerBotGC.jnlp">
 * http://lipp.eit.h-da.de/cb/CleanerBotGC.jnlp</a>. Voraussetzung
 * ist eine installierte Java6 Runtime-Umgebung. Falls diese Umgebung noch
 * nicht auf dem Rechner installiert ist, kann sie
 * <a href="download-jre.html">hier</a> heruntergeladen werden.
 *
 * Sobald die Konsole gestartet wurde, kann sie aus dem C++-Programm heraus
 * angesprochen werden.
 */

#ifndef VACUUMCLEANERWORLD_H_
#define VACUUMCLEANERWORLD_H_

#include <string>
#include <sstream>
#include "cleanerbot/Room.h"
#include "../util/Socket.h"

using std::string;
using std::stringstream;

/**
 * Diese Klasse beschreibt die Welt, in der sich der Staubsauger bewegt.
 * Im einfachsten Fall wird die Klasse zur Visualisierug eines Saugroboters
 * in der Ebene verwendet. Dazu gen�gt der Aufruf der Methode
 * show(double positionX, double positionY, double angle, double diameter).
 *
 * Ein Exemplar der Klasse kann aber auch eine vollst�ndige Umgebung
 * modellieren. Die World ist dann die Wurzel einer Objekthierarchie.
 * Enthaltenes Objekt ist z.&nbsp;B. ein Room.
 *
 * Die Implementierung versucht sich beim Erzeugen mit dem
 * unabh�ngig laufenden Anzeige-Server zu verbinden und verwendet ihn, wenn
 * verf�gbar, f�r die Visualisierung.
 */
class World {
private:
	SocketClient* cmdCon;
	int* refCounter;
	bool traceCommands;
	int sendCommand (const string& cmd);
	int sendCommand (stringstream& cmd);
	int sendCommand(const string& cmd, string& rest);
	int sendCommand(stringstream& cmd, string& rest);
	void decRefCounter ();

	const Room* room;
	double distToRoom (const Ray2D& ray) const;

public:
	/**
	 * Erzeugt eine neue Welt, in der sich der Staubsauger bewegen kann.
	 * Dabei wird versucht, eine Verbindung zu einem Anzeige-Server auf
	 * dem angegebenen Rechner und dem angegebenen
	 * Port aufzubauen. Die Vorgabewerte entsprechen einem auf dem selben
	 * Rechner mit
	 * <a href="http://lipp.eit.h-da.de/intern/vc/VacuumCleanerGC.jnlp">
	 * http://lipp.eit.h-da.de/intern/vc/VacuumCleanerGC.jnlp</a> gestarteten
	 * Anzeige-Server.
	 */
	World(string host = "localhost", int port = 23454);

    /**
     * Erzeugt ein neues Objekt als Kopie des �bergebenen Objekts.
     */
	World(const World & ref);

    virtual ~World();

    World & operator =(const World & ref);

	/** \cond */

    /**
     * Liefert den aktuellen Zustand der Kommandoprotokollierung (s.
     * #setTraceCommands).
     */
    bool getTraceCommands();

    /**
     * Schaltet die Protokollierung der zwischen Programm und Konsole
     * ausgetauschten Kommandos ein oder aus.
     * @param trace <code>true</code> wenn die Kommandos protokolliert
     * werden sollen.
     */
    void setTraceCommands(bool trace);

	/** \endcond */

    /**
     * Stellt einen Staubsauger mit den �bergebenen Eigenschaften in der
     * Welt dar. Wird die Methode das erstem Mal aufgerufen, so wird der
     * Staubsauger an der angegebenen Stelle mit dem angegebene Winkel
     * dargestellt.
     *
     * Bei allen folgenden Aufrufen wird der Staubsauger an die angegebene
     * Stelle bewegt und dann gedreht, so dass er die angegebene Ausrichtung
     * einnimmt.
     *
     * Wird die Methode mit dem Wert 0 f�r den Parameter diameter aufgerufen,
     * so wird der Saugroboter aus der Welt entfernt.
     *
     * @param positionX die Position des Staubsaugers auf der x-Achse.
     * @param positionY die Position des Staubsaugers auf der y-Achse.
     * @param angle der Winkel zwischen der Fahrtrichtung des Staubsaugers
     * und der x-Achse im Bogenma� (rad).
     * @param diameter der Durchmesser des Staubsaugers in Metern.
     */
    virtual void show(double positionX, double positionY, double angle,
    		          double diameter = 0.4);

	/**
	 * Zeigt dem Benutzer in der Statuszeile den �bergebenen Text an.
	 * @param statusText der anzuzeigende Text.
	 */
	virtual void showStatus (string statusText);

	/**
	 * Wartet bis im Konsolenfenster eine Taste gedr�ckt wird und liefert
	 * das Ergebnis als Zeichenkette zur�ck. Die Zeichenkette hat die L�nge
	 * eins, wenn ein einzelner Buchstabe gedr�ckt wurde. Sondertasten werden
	 * als Namen zur�ckgeliefert und haben immer eine L�nge gr��er eins.
	 *
	 * Definiert sind folgende Namen f�r Sondertasten:
	 * <dl>
	 * <dt>up</dt> <dd>Cursortaste nach oben</dd>
	 * <dt>down</dt> <dd>Cursortaste nach unten</dd>
	 * <dt>left</dt> <dd>Cursortaste nach links</dd>
	 * <dt>right</dt> <dd>Cursortaste nach rechts</dd>
	 * </dl>
	 *
	 * @return die gedr�ckte Taste.
	 */
	virtual string getKey();

    /**
     * Bestimmt die Entfernung zwischen der Vorderseite eines Staubsaugers
     * mit den �bergebenen Eigenschaftem
     * und dem am n�chsten stehenden Hindernis im Raum.
     *
     * @param positionX die Position des Staubsaugers auf der x-Achse.
     * @param positionY die Position des Staubsaugers auf der y-Achse.
     * @param angle der Winkel zwischen der Fahrtrichtung des Staubsaugers
     * und der x-Achse im Bogenma� (rad).
     * @param diameter der Durchmesser des Staubsaugers in Metern.
     */
	double distanceFront (double positionX, double positionY, double angle,
	          	  	  	  double diameter = 0.4) const;

    /**
     * Bestimmt die Entfernung zwischen der linken Seite eines Staubsaugers
     * mit den �bergebenen Eigenschaftem
     * und dem am n�chsten stehenden Hindernis im Raum.
     *
     * @param positionX die Position des Staubsaugers auf der x-Achse.
     * @param positionY die Position des Staubsaugers auf der y-Achse.
     * @param angle der Winkel zwischen der Fahrtrichtung des Staubsaugers
     * und der x-Achse im Bogenma� (rad).
     * @param diameter der Durchmesser des Staubsaugers in Metern.
     */
	double distanceLeft (double positionX, double positionY, double angle,
	          	  	     double diameter = 0.4) const;

    /**
     * Bestimmt die Entfernung zwischen der rechten Seite eines Staubsaugers
     * mit den �bergebenen Eigenschaftem
     * und dem am n�chsten stehenden Hindernis im Raum.
     *
     * @param positionX die Position des Staubsaugers auf der x-Achse.
     * @param positionY die Position des Staubsaugers auf der y-Achse.
     * @param angle der Winkel zwischen der Fahrtrichtung des Staubsaugers
     * und der x-Achse im Bogenma� (rad).
     * @param diameter der Durchmesser des Staubsaugers in Metern.
     */
	double distanceRight (double positionX, double positionY, double angle,
	          	  	  	  double diameter = 0.4) const;

    /**
     * Legt den zu der Welt geh�renden Raum fest.
     * @param room der Raum.
     */
    virtual void setRoom(const Room& room);
};

#endif /* VACUUMCLEANERWORLD_H_ */
