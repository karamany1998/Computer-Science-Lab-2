#pragma once
#include "Fahrzeug.h"
#include "Simulationsobjekt.h"

class Weg;

class Fahrrad : public Fahrzeug
{


	public:

	Fahrrad();
	Fahrrad(string name, double maxSpeed);



	virtual double dTanken(double dMenge = numeric_limits<double>::infinity()) override;
	virtual void vAusgeben(ostream&) const override;
	virtual void vSimulieren() override;
	virtual double dGeschwindigkeit() const override;

	void vZeichnen(Weg&) override;



};