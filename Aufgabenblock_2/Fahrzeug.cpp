#include "Fahrzeug.h"
#include "Simulationsobjekt.h"
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"
#include "Weg.h"

#include <iomanip>
#include <limits>
#include <iostream>


//int Fahrzeug::p_iMaxID = 0;  //ID for all Fahrzeuge




Fahrzeug::Fahrzeug() : Simulationsobjekt::Simulationsobjekt(), p_dGesamtStrecke{ 0 }, p_dMaxGeschwindigkeit{ 0 }, p_dGesamtZeit{ 0 }, p_dAbschnittStrecke{ 0 }	//Default Construtor - initializes name to empty string
{
	
	cout << "Created Object --" << "Name: " << p_sName << " ID: " << p_iID << endl;
	
}


Fahrzeug::Fahrzeug(string name) :Simulationsobjekt::Simulationsobjekt(name),  p_dGesamtStrecke{ 0 }  , p_dMaxGeschwindigkeit{ 0 } , p_dGesamtZeit{ 0 } , p_dAbschnittStrecke{ 0 }   //constructor that initializes the name of the Fahrzeug class
{
	
	cout << "Created Object --" << "Name: " << p_sName << " ID: " << p_iID << endl;
	
}

//constructor that takes initializes name and maxSpeed of Fahrzeug
//if maxSpeed is negative, throw logic Error
Fahrzeug::Fahrzeug(string name, double maxSpeed) : Simulationsobjekt::Simulationsobjekt(name) , p_dMaxGeschwindigkeit{ maxSpeed < 0 ? throw std::logic_error("Error: Geschwindigkeit muss positiv sein") : maxSpeed }, p_dGesamtStrecke{ 0 } , p_dGesamtZeit{ 0 } , p_dAbschnittStrecke{ 0 }
{
	
	
	cout << "Created Object --" << "Name: " << p_sName << " ID: " << p_iID <<" and maxSpeed: "<<maxSpeed<< endl;
}




void Fahrzeug::vKopf()
{
	cout << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right);
	std::cout << "ID" << std::setw(13) <<"Name"<< std::setw(20)<< "Geschwindigkeit" << std::setw(15) << "Gesamtstrecke" << std::setw(20)<<"Gesamt Verbrauch" << std::setw(15)<< "Tankinhalt" << endl;
	//cout << setfill('-') << setw(60) << endl;
	
}


//fuer Fahrzeug, return die maximale Geschwindigkeit
double Fahrzeug::dGeschwindigkeit() const
{
	return this->p_dMaxGeschwindigkeit;
}



void Fahrzeug::vAusgeben(ostream& os)  const
{
	double speed = dGeschwindigkeit();
	Simulationsobjekt::vAusgeben(os);   //print out the ID and name of object using Simulationsobjekt vAusgeben Funktion

	cout << std::setw(15) << speed << std::setw(15) << this->p_dGesamtStrecke; //print speed and gesamtStrecke
}



void Fahrzeug::vSimulieren()
{

		double dt = dGlobaleZeit - p_dZeit;   //Zeit zwischen aktueller Zeit und letztem Simulationsschritt
		//double speed = this->dGeschwindigkeit();
		//double zugelegteStrecke = dt * speed;		//Strecke, die das Fahrzeug gefaehrt in dt hat
	
		double zugelegteStrecke = p_pVerhalten->dStrecke(*this, dt);	// Benutze Verhalten-Zeiger, um die zugelegteStrecke zu berechnen. die Strecke ist von Weg abhaengig und Verhalten hat Referenz auf Weg
		//cout << "Time is " << dGlobaleZeit << endl;						
		//cout << "Dstrecke Wert is " << zugelegteStrecke << endl;

		//cout << "------------------------" << endl;

	
		//update von member Variablen
		this->p_dGesamtStrecke += zugelegteStrecke;
		this->p_dAbschnittStrecke += zugelegteStrecke;

		this->p_dGesamtZeit += dt;
		this->p_dZeit = dGlobaleZeit;


}

Fahrzeug::~Fahrzeug()
{
	//cout << "Destroy Object  << Name: " << this->p_sName << "-- ID: " << this->p_iID;
	//cout << endl;

}



//Fahrzeug hat kein Tank, deshalb return 0
 double Fahrzeug::dTanken(double dMenge) 
{
	return 0;
}



 //Falls gesamtStrecke von akutellem Objekt kleiner als die andere, return true
 //sonst return false
 bool Fahrzeug::operator<(Fahrzeug& x)
 {

	 if (this->p_dGesamtStrecke < x.p_dGesamtStrecke)return true;
	 else return false;

 }


 //Assignment(Zuweisung) Operator

 Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other)
 {
	 if (this == &other)return *this;  // kein self-assignment

	 string name = other.p_sName + "-Kopie";		//addiere Kopie auf aktuellem Name
	 this->p_sName = name;
	 this->p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;		//gleiche geschwindigkeit
	 this->p_dGesamtZeit = other.p_dGesamtZeit;						//gleiche gesamtZeit


	 return *this;
 }



 //vNeueStrecke(Weg&) ist ein fahrendes Fahrzeug.
 //p_dAbschnittStrecke is 0 because we just entered the road
 void Fahrzeug::vNeueStrecke(Weg& weg)
 {
	 this->p_pVerhalten = make_unique<Fahren>(weg);
	 this->p_dAbschnittStrecke = 0;   //start distance on new road equal to 0
 }

 // vNeueStrecke(Weg& , double startZeit) ist ein parkendes Fahrzeug, das ab startZeit auf die Strecke fahren wird
 void Fahrzeug::vNeueStrecke(Weg& weg , double startZeit)
 {
	 this->p_pVerhalten = make_unique<Parken>(weg, startZeit);
	
	 this->p_dAbschnittStrecke = 0;   //start distance on new road equal to 0
 }

 //zeichne das Fahrzeug und benutzen bZeichnePKW() Funktion
 void Fahrzeug::vZeichnen(Weg& weg) 
 {
		double relPos = this->p_dAbschnittStrecke / weg.getLength();
		bZeichnePKW(this->p_sName, weg.getName(), relPos, this->dGeschwindigkeit(), 0);
 }

 //Getter von member-variable p_sName
 string Fahrzeug::getName()
 {
	 return this->p_sName;
 }