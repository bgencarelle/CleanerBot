/*
 * Saugroboter.h
 *
 *  Created on: 07.05.2017
 *      Author: ben
 */
#include <stdlib.h>
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <cmath> 
#define _USE_MATH_DEFINES 
#include "cleanerbot/World.h"
using namespace std;

#ifndef SAUGROBOTER_H_
#define SAUGROBOTER_H_


class CSaugroboter
{
private:
	double m_X_Pos;
	double m_Y_Pos;
	double m_DegAngle;
	double m_RadAngle;
	double m_Diameter;
	


	public:
	World m_world;
	CSaugroboter();
	~CSaugroboter();
	double Rad2Deg(double RadAngle);
	double Deg2Rad(double DegAngle);
	void moveMeters(double nMove);
	void rotateDegrees(double AddDeg);
	void displayPositionandAngle();
	void setWorld(World * world);
	void resetDefaults();
	

};



#endif /* SAUGROBOTER_H_ */
