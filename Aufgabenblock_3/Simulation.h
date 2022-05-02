#pragma once
#include "Simulationsobjekt.h"
#include <fstream>
#include <map>
#include <string>

class Kreuzung;
class Simulation 
{


private:

	map<string, shared_ptr<Kreuzung>> mapToSimulationObject;
public: 
	
	virtual void vEinlesen(istream& , bool bMitGrafik = false);
	virtual void vSimulieren();
	void vSimulieren(double , double);

};