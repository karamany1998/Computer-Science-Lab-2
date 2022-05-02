#include "Fahrzeug.h"
#include "Fahrrad.h"
#include <iomanip>
#include <limits>
#include <ostream>
#include "Simulationsobjekt.h"
#include "Weg.h"



Fahrrad::Fahrrad() : Fahrzeug()
{

}

Fahrrad::Fahrrad(string name, double maxSpeed) : Fahrzeug(name , maxSpeed)			//initialize the Fahrrad Variables using the base class constructor
{
	
}

double Fahrrad::dTanken(double dMenge)		//Wir koennen nicht Fahrrad Tanken, deshalb return 0
{
	return 0;
}


double Fahrrad::dGeschwindigkeit() const
{

	double currentSpeed = this->p_dMaxGeschwindigkeit;
	double distance = this->p_dGesamtStrecke;
	while (distance >= 20)				
	{
		currentSpeed = currentSpeed * 0.90; //geschwindigkeit nimmt jede 20km um 10% ab
		distance -= 20;
	}

	if (currentSpeed <= 12)currentSpeed = 12;

	return currentSpeed;
}

	
void Fahrrad::vAusgeben(ostream& os) const			//virtual functiom zum Ausgeben von Fahrrad
{
	double speed = dGeschwindigkeit();
	Fahrzeug::vAusgeben(os);				//Benutze die vAusgeben Methode von Fahrzeug Klasse
	//os << this->p_iID << std::setw(15) << this->p_sName << std::setw(15) << speed << std::setw(15) << this->p_dGesamtStrecke;
}


void Fahrrad::vEinlesen(istream& is) {

	Fahrzeug::vEinlesen(is);

}

void Fahrrad::vSimulieren()
{
	Fahrzeug::vSimulieren();
}




void Fahrrad::vZeichnen(Weg& weg)
{
	//p_dAbschnittStrecke gibt die zugelegte Strecke auf aktuellem Weg
	//relPos ist dann gleich p_dAbschnittStrecke / weg Laenge

	double relPos = this->p_dAbschnittStrecke / weg.getLength();		
	bZeichneFahrrad(this->p_sName, weg.getName(), relPos, this->dGeschwindigkeit());	//zeichne Fahhrad auf Simulationsfenster
}