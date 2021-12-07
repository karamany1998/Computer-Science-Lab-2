

#include "Parken.h"
#include "Simulationsobjekt.h"
#include "Losfahren.h"



//Unterklassee von Verhalten 
Parken::Parken(Weg& weg, double startZeit) : Verhalten(weg) , p_dStartZeit{ startZeit }
{


}


//dStrecke ist die zugelegte Strecke

double Parken::dStrecke(Fahrzeug& aFzg, double startZeit)
{
	if (this->p_dStartZeit > dGlobaleZeit)return 0.0;		//Strecke ist immer null falls, dGlobalZeit kleiner als p_dStartZeit vom parkenden Fahrzeug
	 
	throw Losfahren( aFzg  , p_pWeg);			//sonst throw Losfahren und mach das Fahrzeug fahren
	

}

