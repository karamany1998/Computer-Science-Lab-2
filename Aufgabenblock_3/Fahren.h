#pragma once

#include "Verhalten.h"

class Fahren : public Verhalten
{

public:

	Fahren(Weg& weg) : Verhalten::Verhalten(weg)
	{

	}

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
	{
		return Verhalten::dStrecke(aFzg, dZeitIntervall);
	}
	


};