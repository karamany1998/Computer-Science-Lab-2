
#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "Simulationsobjekt.h"
#include <iterator>
#include "Tempolimit.h"
#include <iomanip>
#include <limits>
#include <iostream>
#include <list>
#include "Kreuzung.h"


//cancel_change(3)
//Weg::Weg() : Simulationsobjekt::Simulationsobjekt(), p_dLaenge(0) , p_eTempolimit{Tempolimit::Autobahn} , p_bUeberholverbot{true}
//{}

//Weg::Weg(string name, double lang, int tempoLimit) : Simulationsobjekt::Simulationsobjekt(name), p_dLaenge(lang) , p_eTempolimit{Tempolimit(tempoLimit)}
//{}

//cancel_change(3)
//Weg::Weg(std::string name, double lang, Tempolimit tempoLimit) : Simulationsobjekt::Simulationsobjekt(name), p_dLaenge(lang) , p_eTempolimit{ tempoLimit } , p_bUeberholverbot{true} , p_dVirtuelleSchranke{ lang }
//{}

//cancel_change(3)
//Weg::Weg(std::string name, double lang, bool UeberholVerbot, Tempolimit tempoLimit ) : Simulationsobjekt::Simulationsobjekt(name), p_dLaenge(lang), p_bUeberholverbot{ UeberholVerbot } ,  p_eTempolimit{ tempoLimit } , p_dVirtuelleSchranke{ lang } 
//{}

//Weg::Weg(std::string name, double lang, bool UeberholVerbot, weak_ptr<Kreuzung> ziel, Tempolimit tempoLimit ) : Simulationsobjekt::Simulationsobjekt(name), p_dLaenge(lang), p_bUeberholverbot{ UeberholVerbot }, p_eTempolimit{ tempoLimit }, p_dVirtuelleSchranke{ lang } , p_pZielKreuzung{ziel}
//{}


Weg::Weg(std::string sName, double uLaenge, Tempolimit eTempolimit , bool bUeberholverbot , std::shared_ptr<Kreuzung> pZiel ) : Simulationsobjekt::Simulationsobjekt(sName), p_dLaenge(uLaenge), p_bUeberholverbot{ bUeberholverbot }, p_eTempolimit{ eTempolimit }, p_dVirtuelleSchranke{ uLaenge }, p_pZielKreuzung{ pZiel }
{}
//Weg(std::string name, double lang, bool UeberholVerbot, Weg Ruckweg , Kreuzung ziel , Tempolimit tempoLimit = Tempolimit::Autobahn)
//Weg::Weg(std::string name, double lang, bool UeberholVerbot, weak_ptr<Weg> Ruckweg, weak_ptr<Kreuzung> ziel , Tempolimit tempoLimit) : Weg::Weg(name, lang, UeberholVerbot, tempoLimit) , p_pZielKreuzung{ ziel } , p_pRuckweg{ Ruckweg }
//{

//}

void Weg::vAusgeben(ostream& os)  const
{

	Simulationsobjekt::vAusgeben(os);
	os << std::setw(15);
	os << this->p_dLaenge << std::setw(15);
	os << "( ";

	for (auto &ptr : p_pFahrzeuge)
	{
		os << ptr->getName() << "   ";
		
	}

	os << ")"; 

}




void Weg::vKopf()
{

	cout << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right);
	std::cout << "ID" << std::setw(13) << "Name" << std::setw(20) << "Laenge" << std::setw(15) << "Fahrzeuge";
}


/*
double getTempoLimit(int whichStreet) {

	Tempolimit tempo = Tempolimit(whichStreet);

	if (tempo == Tempolimit::Innerorts)return (double)50;
	else if (tempo == Tempolimit::Landstrasse)return (double)100;
	else if (tempo == Tempolimit::Autobahn)return (double)numeric_limits<int>::max();


	//default ist ein Autobahn
	return (double)numeric_limits<int>::max();

}
*/

// Simulation vom Weg 
void Weg::vSimulieren()
{
	this->p_pFahrzeuge.vAktualisieren();		//aktualisiere vor Simulation von Weg
	using iterator = typename std::list<unique_ptr<Fahrzeug>>::iterator;

	
	for (auto&ptr : p_pFahrzeuge)
	{
		
		double ueberholVerbot = this->p_dVirtuelleSchranke;	//zwei Variable addiert, weil Fahrzeug geloescht wird, wenn Fahrausnahme passiert und deshalb moechte ich die Info vorher speichern.
		double Inhalt = ptr->getInhalt();
		try
		{
			
			(ptr)->vSimulieren();		//simulieren und zeichne jedes Fahrzeug
			(ptr)->vZeichnen(*this);

			
		}
		catch (Fahrausnahme& ex)	//Wenn Fahrzeug am Ende, setzen wir virtuelle Schranke = Weglaenge
		{
			ueberholVerbot = (ptr)->getAbschnitt(); 
			if (ueberholVerbot == 0)ueberholVerbot = this->p_dLaenge;
			ex.vBearbeiten();
			
		}

		//(PART 3) - Jedes Mal eine Simulation stattfindet, aendern wir die "virtuelle Schranke",
		//			so dass naechste Fahrzeuge nicht dieses Fahrzeug ueberholen
		// parkende -- Wegende Fahrend -- Weganfang fahrend 
		if (this->p_bUeberholverbot) {

			if (Inhalt != 0)	//falls PKW nicht leer, dann ist es noch ein Hinderniss, sondern betrachten wir das PKW nicht
				this->p_dVirtuelleSchranke = ueberholVerbot;
			 
		}
	}
	this->p_pFahrzeuge.vAktualisieren();	//aktualisiere nach Simulation von Weg
	return; 

 }

double Weg::getTempoLimit()
{
	switch (this->p_eTempolimit)
	{
	case Tempolimit::Innerorts:
		return 50.0;
		break;
	case Tempolimit::Landstrasse:
		return 100.0;
		break;
	case Tempolimit::Autobahn:
		return (double)numeric_limits<int>::max();
		break;

	default:
		return (double)numeric_limits<int>::max();
	}
}


//platziert ein fahrendes Fahrzeug auf diesem Weg
void Weg::vAnnahme(unique_ptr<Fahrzeug> Fzg)
{
	if (Fzg == nullptr) return;
	Fzg->vNeueStrecke((*this));  //*this is reference to current Weg-Object which goes to vNeueStrecke(Weg&)
	p_pFahrzeuge.push_back(std::move(Fzg));
	
	
	return;
}

//platziert ein parkendes Fahrzeug , das ab startZeit fahren soll, auf diesem Weg

void Weg::vAnnahme(unique_ptr<Fahrzeug> Fzg, double startZeit)
{
	if (Fzg == nullptr)return;
	Fzg->vNeueStrecke((*this), startZeit);
	p_pFahrzeuge.push_front(std::move(Fzg));
	
}


//erase the car aFzg from list of unique pointers to Fahrzeug
unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& aFzg)
{
	
	unique_ptr<Fahrzeug> park_to_Fahr;
	auto it = make_unique<Fahrzeug>();
	unique_ptr<Fahrzeug> deletedCar;

	for (list<unique_ptr<Fahrzeug>>::iterator it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if (*it == nullptr)continue;	//if nullptr, then go next

		if (**it == aFzg)		//if aFzg is found
		{
			deletedCar = move(*it);	//change ownership of object to deletedCar pointer
			p_pFahrzeuge.erase(it);  //erase car from weg 
			break; //exit loop
		}
	}

	return deletedCar;		//return the pointer to caller
}



double Weg::getSchranke() {


	if (!this->p_bUeberholverbot) return this->p_dLaenge;		//kein Ueberholverbot, man kann auf dem gesamten Weg fahren und Fahrzeuge ueberholen

	//wenn es ein Ueberholverbot gibt, dann return 
	return this->p_dVirtuelleSchranke;
}
