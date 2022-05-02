#pragma once
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <vector>
#include <string>

#include <list>

class Fahrzeug;
class Weg;


class Kreuzung : public Simulationsobjekt
{


private : 

	vector<shared_ptr<Weg>> p_pWege;
	double p_dTankstelle;



public: 

	Kreuzung();
	Kreuzung(string name);
	Kreuzung(string name, double tankeStelle);


	static void vVerbinde(string Hinweg , string Ruckweg , double weglaenge, shared_ptr<Kreuzung> krz1, shared_ptr<Kreuzung> krz2, Tempolimit tempoLimit = Tempolimit::Autobahn, bool Ueberholverbot = true);

	void vTanken(Fahrzeug&); //tanken von Fahrzeug an der Kreuzung


	void vAnnahme(unique_ptr<Fahrzeug>, double Zeit);

	virtual void vSimulieren() override;
	virtual void vEinlesen(istream&);
	//virtual void vEinlesen(istream& is, bool bMitGrafik = false);

	Weg& pZufaelligerWeg(Weg&);


	string getName()
	{
		return Simulationsobjekt::p_sName;
	}


	double getTank() {

		return this->p_dTankstelle;
	}

};