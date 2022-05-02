#pragma once
#include "Fahrausnahme.h"


/*
	Streckenende ist Unterklasse von Fahrausnahme


*/


class Streckenende : public Fahrausnahme {


public:
	Streckenende(Fahrzeug& , Weg&);
	virtual void vBearbeiten();
};