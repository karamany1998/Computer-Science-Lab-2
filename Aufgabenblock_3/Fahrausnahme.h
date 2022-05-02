#pragma once
#include <iostream>       // std::cerr
#include <typeinfo>       // operator typeid
#include <exception>      // std::exception
#include "Fahrzeug.h"
#include "Weg.h"


class Fahrausnahme : public std::exception
{

protected:

	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;


public : 


	Fahrausnahme(Fahrzeug&, Weg&);

	virtual void vBearbeiten() = 0; 


};