#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <random >





Kreuzung::Kreuzung() : Simulationsobjekt(""), p_dTankstelle(0.0)
{

}
Kreuzung::Kreuzung(string name) : Simulationsobjekt(name) , p_dTankstelle(0.0)
{

}

Kreuzung::Kreuzung(string name, double tankeStelle) : Simulationsobjekt(name) , p_dTankstelle{tankeStelle}
{

}

//static void vVerbinde(string Hinweg , string Ruckweg , double weglaenge, Kreuzung krz1, Kreuzung krz2, Tempolimit tempoLimit = Tempolimit::Autobahn, bool Ueberholverbot = true)
//krz1 = startKreuzung
//krz2 = zielKreuzung
void Kreuzung::vVerbinde(string nameHinweg, string nameRuckweg, double weglaenge, shared_ptr<Kreuzung> startKreuzung, shared_ptr<Kreuzung> zielKreuzung, Tempolimit tempoLimit , bool Ueberholverbot ) {

	
	
	//Weg(std::string sName, double uLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn, bool bUeberholverbot = true, std::shared_ptr<Kreuzung> pZiel = nullptr) 
	
	//erzeuge die Wege
	shared_ptr<Weg> hinweg = make_shared<Weg>(nameHinweg , weglaenge, tempoLimit, Ueberholverbot, zielKreuzung);
	shared_ptr<Weg> ruckweg = make_shared<Weg>(nameRuckweg, weglaenge, tempoLimit,  Ueberholverbot, startKreuzung );

	
	//Wege kennen ihre Ruckwege
	hinweg->setRuckWeg(ruckweg);
	ruckweg->setRuckWeg(hinweg);
	

	startKreuzung->p_pWege.push_back(hinweg);
	zielKreuzung->p_pWege.push_back(ruckweg);



}


void Kreuzung::vTanken(Fahrzeug& Fzg) {
	
	if (this->p_dTankstelle > 0)
	{
		double getankteMenge = Fzg.dTanken();
		this->p_dTankstelle -= getankteMenge;
		if (p_dTankstelle < 0) p_dTankstelle = 0; //falls nicht genug Gas, dann benutze Reserve 

	}
	
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFzg, double Zeit) {

	this->vTanken(*pFzg); //Tanken des Fahrzeugs
	//void vAnnahme(unique_ptr<Fahrzeug> Fzg, double startZeit) -->Funktion, die man benutze um Fahrzeug auf dem Weg zu addieren
	if(p_pWege.size() >=1)
	p_pWege[0]->vAnnahme(move(pFzg), Zeit);	//addiere Fahrzeug zum ersten Weg

}



void Kreuzung::vSimulieren() {

	for (auto weg : this->p_pWege) {		//Simuliere alle Wege von dieser Kreuzung
		weg->vSimulieren();
	}
}



Weg& Kreuzung::pZufaelligerWeg(Weg& weg)
{

	int numWeg = p_pWege.size();

	
	if (numWeg == 1) //Sackgasse 
	return *p_pWege[0];

	static std::mt19937 device(0);
	std::uniform_int_distribution <int > dist(0, numWeg - 1);		//Waehle Zufaelligen Weg durch Randon-Number generator
	
	int zufWegIndex;
	do
	{
	    zufWegIndex = dist(device);
		

	} while (p_pWege[zufWegIndex]->getRuckWeg().getName() == weg.getName());	//ueberpruefe, dass wir nicht auf derselbe Strasse fahren

	return *p_pWege[zufWegIndex];  


}

void Kreuzung::vEinlesen(istream& is ){
	
	Simulationsobjekt::vEinlesen(is);
	is >> this->p_dTankstelle;
}