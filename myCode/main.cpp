// GIT-Labor
// main.h

////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
// TODO: Fügen Sie hier weitere benötigte Header-Dateien ein
#include "CSaugroboter.h"


	// Erspart den scope vor Objekte der
						// C++-Standard-Bibliothek zu schreiben
						// z.B. statt "std::cout" kann man "cout" schreiben

// Inkludieren Sie die Header-Datei Ihrer Klasse


// Hauptprogramm
// Dient als Testrahmen, von hier aus werden die Klassen aufgerufen
int main (void)
{
	CSaugroboter C;

	while (1)
	{
	C.displayPositionandAngle();
	cout << "CleanerBot gestarted." << endl << endl;
	int rot = 0;
	cout << "enter rotation (in degrees) relative to current" << endl;
	cin >> rot;
	C.rotateDegrees(rot);
	int move = 0;
	cout << "enter amount to move" << endl;
	cin >> move;
	C.moveMeters(move);
	C.displayPositionandAngle();
	//C.resetDefaults();

	}

	return 0;
}
