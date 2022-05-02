

#include "Simulationsobjekt.h"

#include <iomanip>
#include <limits>
#include <ostream>


int Simulationsobjekt::p_iMaxID = 0;



Simulationsobjekt::Simulationsobjekt() : p_sName{ "" }, p_iID{ p_iMaxID }, p_dZeit{ 0 }
{
	p_iMaxID++;
}
Simulationsobjekt::Simulationsobjekt(string name) : p_sName{ name } , p_iID{ p_iMaxID} , p_dZeit{ 0 }
{
	p_iMaxID++;
}

Simulationsobjekt::~Simulationsobjekt()
{

	cout << "Destroy Object " << "Name: " << this->p_sName << "-- ID: " << this->p_iID;
	cout << endl;
}


void Simulationsobjekt::vAusgeben(ostream&) const
{

	cout << this->p_iID << std::setw(15) << this->p_sName;
}





void Simulationsobjekt::setStartTime(double x) {

	this->p_dZeit = x;
}



void Simulationsobjekt::vEinlesen(istream& is )
{
	is >> this->p_sName;
}