/*
 * CSaugroboter.cpp
 *
 *  Created on: 07.05.2017
 *      Author: ben
 */
#include "CSaugroboter.h"

CSaugroboter::CSaugroboter() {

	m_X_Pos = 0;
	m_Y_Pos = 0;
	m_RadAngle = 0;
	m_DegAngle = 0;
	m_Diameter = 1;


}

double CSaugroboter::Rad2Deg(double RadAngle) {
	double DegOut;
	DegOut= (RadAngle * 180)/M_PI;
	return DegOut;
}

double CSaugroboter::Deg2Rad(double DegAngle) {
	double RadOut;
	while (DegAngle >360.)
	{
		DegAngle -=360;
	}
	while (DegAngle < 0.)
	{
		DegAngle +=360;
	}
		RadOut = DegAngle*M_PI/180;

		return RadOut;
}

void CSaugroboter::moveMeters(double nMove) 
{
	m_X_Pos = m_X_Pos + cos(m_RadAngle)*nMove;
	m_Y_Pos = m_Y_Pos + sin(m_RadAngle)*nMove;
	m_world.show(m_X_Pos,m_Y_Pos,m_RadAngle, .4);
	return;

}


void CSaugroboter::rotateDegrees(double AddDeg) {
	m_DegAngle += AddDeg;
	while (m_DegAngle <0)
	{
		m_DegAngle += 360;
	}
	while (m_DegAngle > 360)
	{
		m_DegAngle -= 360;
	}

	m_RadAngle = Deg2Rad(m_DegAngle);
	m_world.show(m_X_Pos,m_Y_Pos,m_RadAngle, .4);
	return;
}

void CSaugroboter::displayPositionandAngle() {
	m_world.show(m_X_Pos,m_Y_Pos,m_RadAngle, .4);
	cout << "X Y pos: "<< m_X_Pos <<"," << m_Y_Pos << endl;
	cout << "angle in Degrees:" << m_DegAngle << " in Radians " << m_RadAngle <<endl;
	return;
}

void CSaugroboter::setWorld(World * world) {
	m_world.show(m_X_Pos,m_Y_Pos,m_RadAngle, .4);

	return;
}


CSaugroboter::~CSaugroboter() {

	cout << "loops there is " << endl;
}

void CSaugroboter::resetDefaults() {
	m_X_Pos = 0;
	m_Y_Pos = 0;
	m_RadAngle = 0;
	m_DegAngle = 0;
	m_Diameter = 1;
}
