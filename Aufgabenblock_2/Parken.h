#pragma once

#include "Verhalten.h"

class Parken : public Verhalten
{



protected: 

	double p_dStartZeit;
public:

	 
	virtual double dStrecke(Fahrzeug&, double);
	Parken(Weg& weg, double startZeit);

};