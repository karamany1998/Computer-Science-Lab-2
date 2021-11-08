#include "Fahrzeug.h"
#include <iomanip>
#include <limits>
#include <iostream>

int Fahrzeug::p_iMaxID = 0;  //ID for all Fahrzeuge




Fahrzeug::Fahrzeug() : p_sName{ "" }, p_iID{ p_iMaxID }, p_dGesamtStrecke{ 0 }, p_dGesamtZeit{ 0 }, p_dZeit{ 0 }, p_dMaxGeschwindigkeit{ 0 }	//Default Construtor - initializes name to empty string
{
	cout << "Created Object --" << "Name: " << p_sName << " ID: " << p_iID << endl;
	p_iMaxID++;
}


Fahrzeug::Fahrzeug(string name) : p_sName{ name }, p_iID{ p_iMaxID }, p_dGesamtStrecke{ 0 }, p_dGesamtZeit{ 0 }  , p_dZeit{ 0 } , p_dMaxGeschwindigkeit{ 0 }   //constructor that initializes the name of the Fahrzeug class
{

	cout << "Created Object --" << "Name: " << p_sName << " ID: " << p_iID << endl;
	p_iMaxID++;
}

Fahrzeug::Fahrzeug(string name, double maxSpeed) : p_iID{ p_iMaxID }, p_sName{ name }, p_dMaxGeschwindigkeit{ maxSpeed < 0 ? throw std::logic_error("Error: Geschwindigkeit muss positiv sein") : maxSpeed }, p_dGesamtStrecke{ 0 }, p_dGesamtZeit{ 0 }, p_dZeit{ 0 }
{
	
	p_iMaxID++;
	cout << "Created Object --" << "Name: " << p_sName << " ID: " << p_iID <<" and maxSpeed: "<<maxSpeed<< endl;
	


}

void Fahrzeug::vKopf()
{
	cout << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right);
	std::cout << "ID" << std::setw(13) <<"Name"<< std::setw(20)<< "Geschwindigkeit" << std::setw(15) << "Gesamtstrecke" << std::setw(20)<<"Gesamt Verbrauch" << std::setw(15)<< "Tankinhalt" << endl;
	//cout << setfill('-') << setw(60) << endl;
	
}

double Fahrzeug::dGeschwindigkeit() const
{
	return this->p_dMaxGeschwindigkeit;
}

void Fahrzeug::vAusgeben(ostream&)  const
{
	double speed = dGeschwindigkeit();
	cout << this->p_iID << std::setw(15) << this->p_sName << std::setw(15) << speed << std::setw(15) << this->p_dGesamtStrecke;

}

void Fahrzeug::vSimulieren()
{

		double dt = dGlobaleZeit - p_dZeit;   //Zeit zwischen aktueller Zeit und letztem Simulationsschritt
		double speed = this->dGeschwindigkeit();
		double zugelegteStrecke = dt * speed;		//Strecke, die das Fahrzeug gefaehrt in dt hat

		//update von member Variablen
		this->p_dGesamtStrecke += zugelegteStrecke;
		this->p_dGesamtZeit += dt;
		this->p_dZeit = dGlobaleZeit;


}

Fahrzeug::~Fahrzeug()
{
	cout << "Destroy Object " << "Name: " << this->p_sName << "-- ID: " << this->p_iID;
	cout << endl;
}




 double Fahrzeug::dTanken(double dMenge) 
{
	return 0;
}




 bool Fahrzeug::operator<(Fahrzeug& x)
 {

	 if (this->p_dGesamtStrecke < x.p_dGesamtStrecke)return true;
	 else return false;

 }



 Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other)
 {
	 if (this == &other)return *this;  //self-assignment

	 string name = other.p_sName + "-Kopie";
	 this->p_sName = name;
	 this->p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
	 this->p_dGesamtZeit = other.p_dGesamtZeit;


	 return *this;
 }