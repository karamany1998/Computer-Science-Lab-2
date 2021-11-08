#include "Fahrzeug.h"
#include "Fahrrad.h"
#include <iomanip>
#include <limits>
#include <ostream>




Fahrrad::Fahrrad() : Fahrzeug()
{

}

Fahrrad::Fahrrad(string name, double maxSpeed) : Fahrzeug(name , maxSpeed)			//initialize the Fahrrad Variables using the base class constructor
{
	
}

double Fahrrad::dTanken(double dMenge)
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


void Fahrrad::vAusgeben(ostream& os) const
{
	double speed = dGeschwindigkeit();
	os << this->p_iID << "    " << this->p_sName << "   " << speed << "    " << this->p_dGesamtStrecke;
}

void Fahrrad::vSimulieren()
{
	Fahrzeug::vSimulieren();
}


