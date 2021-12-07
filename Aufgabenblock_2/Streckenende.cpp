#include "Streckenende.h"






Streckenende::Streckenende(Fahrzeug& Fzg, Weg& weg) : Fahrausnahme(Fzg, weg)
{

}


// vBearbeiten ist eine virtuelle Methode, die fuer fahrende Fahrzeuge, die am Ende des aktuellen Weg sind

void Streckenende::vBearbeiten()
{
	cout << "Ausnahme: Streckenende auf Strasse (" << this->p_pWeg.getName() << " )" << "   Name: "<< this->p_pFahrzeug.getName() << endl;

	p_pWeg.pAbgabe(this->p_pFahrzeug);  //pAbgabe deletes the car from list of Fahrzeuge and returns a unique_ptr<Fahrzeug>...Here we only need to delete the car.

}