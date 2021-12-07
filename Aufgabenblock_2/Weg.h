#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"
#include "vertagt_aktion.h"
#include <iostream>
#include <limits>
#include <string>
#include <list>

using namespace std;

class Fahrzeug;
class PKW;
class Fahrrad;


class Weg : public Simulationsobjekt
{


private : 

	double p_dLaenge;
	//list<unique_ptr<Fahrzeug>> p_pFahrzeuge;
	vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;		//VListe anstatt einfache liste, um Probleme bei erase() and push_front() and push_back() zu vermeiden

	Tempolimit p_eTempolimit;

public: 

	Weg();

	Weg(string name, double lang, Tempolimit tempoLimit = Tempolimit::Autobahn );
	//Weg(string name, double lang, int tempoLimit = numeric_limits<int>::max());


	virtual void vAusgeben(ostream& os) const;


	static void vKopf();

	virtual void vSimulieren();
	
	
	double getTempoLimit();


	void vAnnahme(unique_ptr<Fahrzeug> Fzg);
	void vAnnahme(unique_ptr<Fahrzeug> Fzg, double startZeit);


	//Getters
	double getLength()
	{
		return this->p_dLaenge;
	}

	
	


	string getName()
	{
		return this->p_sName;
	}


	unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);

};

