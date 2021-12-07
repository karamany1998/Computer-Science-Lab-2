#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Simulationsobjekt.h"
#include "Streckenende.h"
#include <iostream>



Verhalten::Verhalten(Weg& weg) : p_pWeg {weg}
{

}





double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double speed = aFzg.dGeschwindigkeit();
	double zugelegteStrecke = speed * dZeitIntervall;		//Strecke, die das Fahrzeug gefaehrt in dZeitIntervall hat

	if (aFzg.getAbschnitt() == p_pWeg.getLength())  // Falls Fahrzeug am Ende des Weges ist, dann throw ein Streckende(aFzg, p_pWeg) Exception
	{
		
		//cout << " Erreicht Ende des Weges " << endl;
		//cout << "Dieser Fahrzeug mit ID: "
		throw Streckenende(aFzg, p_pWeg);		//throw Exception() : Fahrzeug wird geloescht
	}


	//falls Weg ueberschreiten, dann return nur die verbleinde Strecke( length of road - current position of road)
	if (zugelegteStrecke + aFzg.getAbschnitt() >= p_pWeg.getLength())  //Fahrzeug erreicht Ende des Weges 
	{
		return p_pWeg.getLength() - aFzg.getAbschnitt();
	
	}

	return zugelegteStrecke;			//Fahrzeug erreicht nicht Ende des Weges
}