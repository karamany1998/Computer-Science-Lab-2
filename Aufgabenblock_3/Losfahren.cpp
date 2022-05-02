#include "Losfahren.h"
#include "Simulationsobjekt.h"

/*
	Losfahren is a derived class from the Fahrausnahme class
	Losfahren macht das parkende Fahrzeug in ein fahrendes Fahrzeug
	aufgerufen wenn diese Bedingung gilt : globalZeit >= startZeit vom parkenden Fahrzeug
*/

Losfahren::Losfahren(Fahrzeug& Fzg, Weg& weg) : Fahrausnahme(Fzg, weg)		//use Fahrausnahme Constructor to construct the Losfahren object
{

}


void Losfahren::vBearbeiten()				//virtual function that gets called for parked cars 
{

	//cout << "Zeit :" << dGlobaleZeit << endl;
	cout << "Ausnahme: Losfahren ----" << this->p_pWeg.getName() << " ";		//output the Ausnahme and name of road
	cout << this->p_pFahrzeug.getName() << endl;								//output name of car 

	unique_ptr<Fahrzeug> movingCar = p_pWeg.pAbgabe(p_pFahrzeug); //delete car from weg and get back pointer

	p_pWeg.vAnnahme(move(movingCar));		//fuege Fahrzeug in weg als fahrendes Fahrzeug ein
	

}