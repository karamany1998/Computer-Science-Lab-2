#pragma once

#include "Fahrzeug.h"
#include <string>

class PKW : public Fahrzeug
{

	private : 

		double p_dVerbrauch;  //wie viel Liter verbrauch das PKW jede 100 km
		double p_dTankvolumen;	//total Volumen des Tanks von dem PKW
		double p_dTankinhalt;	//aktueller Inhalt vom Tank(leer = keine Fortbewegung)

	public: 
		PKW(); //default constructor
		//PKW(string name, double maxSpeed, double volumen = 55);  //PKW Constructors
		PKW(string name, double maxSpeed , double verbrauch, double volumen = 55);		//PKW Constructors

		
		//virtual functions
		virtual double dTanken(double) override;
		virtual void vAusgeben(ostream&) const override;
		virtual void vSimulieren() override;
		virtual double dGeschwindigkeit() const override;




};