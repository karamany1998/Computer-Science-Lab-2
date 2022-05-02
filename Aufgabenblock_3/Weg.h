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

class Kreuzung;
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
	bool p_bUeberholverbot;

	double p_dVirtuelleSchranke;

	weak_ptr<Weg> p_pRuckweg;
	weak_ptr<Kreuzung> p_pZielKreuzung;

public: 

	Weg();

	//Weg(std::string name, double lang, Tempolimit tempoLimit = Tempolimit::Autobahn );

	//Weg(std::string name, double lang, bool UeberholVerbot , Tempolimit tempoLimit = Tempolimit::Autobahn);

	//Weg(std::string name, double lang, bool UeberholVerbot, weak_ptr<Weg> Ruckweg, weak_ptr<Kreuzung> ziel , Tempolimit tempoLimit)
	//Weg(std::string name, double lang, bool UeberholVerbot, weak_ptr<Kreuzung> ziel, Tempolimit tempoLimit = Tempolimit::Autobahn);
	
	//constructor should be :
	Weg(std::string sName, double uLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn, bool bUeberholverbot = true, std::shared_ptr<Kreuzung> pZiel = nullptr);



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


	double getSchranke();		//function that returns the position of the farthest vehicle on the road.


	void setRuckWeg(weak_ptr<Weg> weg) {
		this->p_pRuckweg = weg;
	}


	Kreuzung& getZielKreuzung() {

		return *(p_pZielKreuzung.lock());

	}

	Weg& getRuckWeg() {

		return *(p_pRuckweg.lock());
	}
	


};

