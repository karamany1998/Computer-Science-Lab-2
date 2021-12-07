#pragma once

class Weg;
class Fahrzeug;

class Verhalten
{

protected:
	Weg& p_pWeg;


public:
	Verhalten();
	Verhalten(Weg&);
	virtual double dStrecke(Fahrzeug&, double) = 0; 


	Weg& getWeg(){   //return Referenze auf weg fuer das PKW dGeschwindigkeit Funktion
		return p_pWeg;
	}





};