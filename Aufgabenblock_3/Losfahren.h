#pragma once
#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme
{



public:

	Losfahren(Fahrzeug& Fzg, Weg& weg);
	
	virtual void vBearbeiten();


};