#include "PKW.h"
#include <iomanip>
#include <iostream>
#include "Fahrzeug.h"
#include "Simulationsobjekt.h"
#include <string>
#include <ostream>
#include "SimuClient.h"
#include "Verhalten.h"
#include "Weg.h"


PKW::PKW() : Fahrzeug(), p_dVerbrauch{ 0 }, p_dTankvolumen{ 0 }, p_dTankinhalt{ 0 }
{

}

PKW::PKW(string name, double maxSpeed, double verbrauch, double volumen) : Fahrzeug(name, maxSpeed), p_dVerbrauch{ verbrauch }, p_dTankvolumen{ volumen }, p_dTankinhalt{ volumen / 2 }
{


}


PKW::PKW(string name, double speed) : Fahrzeug(name, speed)			
{

}


double PKW::dTanken(double dMenge = numeric_limits<double>::infinity())
{

	if (this->p_dTankvolumen-this->p_dTankinhalt <= dMenge)	// wenn dMenge zu viel ist, dann ist das Tank voll
	{
		double retVal = p_dTankvolumen - p_dTankinhalt;  //verbleibende Menge
		this->p_dTankinhalt = this->p_dTankvolumen;		//Tank ist voll
		return retVal;
	}
	else
	{
		this->p_dTankvolumen += dMenge;
		return dMenge;
	}

}


void PKW::vAusgeben(ostream& os) const
{
	Fahrzeug::vAusgeben(os);
	double gesamtVerbrauch = this->p_dGesamtStrecke * (this->p_dVerbrauch/100.0);
	os << setfill(' ');
	os<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)  << std::setw(15) <<gesamtVerbrauch << std::setw(15) << this->p_dTankinhalt;


}


void PKW::vSimulieren() {

	double timeDT = dGlobaleZeit - this->p_dZeit;	//time since last simulation
	

	if (p_dTankinhalt > 0)
	{
		double streckeBefore = this->p_dGesamtStrecke;
		Fahrzeug::vSimulieren();		
		double streckeAfter = this->p_dGesamtStrecke;
		double strecke = streckeAfter - streckeBefore;  //total distance traveled if PKW moves at p_dMaxGeschwindigkeit
		cout << "Zeit :" << dGlobaleZeit << endl;
		cout << "dStrecke " << strecke << endl;
		double benutzteLiter = (double)strecke * (double)(this->p_dVerbrauch / (double)100.0);			//liter used over strecke

		p_dTankinhalt -= benutzteLiter;	//PKW uses benutzteLiter 
		//p_dGesamtStrecke += strecke;
		if (p_dTankinhalt < 0)p_dTankinhalt = 0;
	}
	//update von Variablen
	//this->p_dGesamtZeit += timeDT;
	//this->p_dZeit = dGlobaleZeit;
	
}


 double PKW::dGeschwindigkeit() const
{
	 Weg& weg = this->p_pVerhalten->getWeg();

	 double tempo = weg.getTempoLimit();		//falls Tempolimit von Weg kleiner als p_dMaxGeschwindigkeit fuer das PKW, dann Fahren wir mit Tempolimit vom Weg
	 if (this->p_dMaxGeschwindigkeit >  tempo)
	 {
		 return tempo;
	 }
	 
	 return this->p_dMaxGeschwindigkeit;		//sonst fahren wir mit p_dMaxGeschwindigkeit
}


//Zeichne PKW auf Fenster
 void PKW::vZeichnen(Weg& weg)
 {
	 double relPos = this->p_dAbschnittStrecke / weg.getLength();
	 double currSpeed = this->dGeschwindigkeit();
	 bZeichnePKW(this->p_sName, weg.getName(), relPos, currSpeed, this->p_dTankinhalt);
	 
 }