#include "Streckenende.h"
#include "Kreuzung.h"





Streckenende::Streckenende(Fahrzeug& Fzg, Weg& weg) : Fahrausnahme(Fzg, weg)
{

}


// vBearbeiten ist eine virtuelle Methode, die fuer fahrende Fahrzeuge, die am Ende des aktuellen Weg sind
void Streckenende::vBearbeiten()
{
	cout << "Ausnahme: Streckenende auf Strasse (" << this->p_pWeg.getName() << " )" << " Fahrzeug Name: "<< this->p_pFahrzeug.getName() << endl;


	//CHANGE FOR AB3
	//Wir sind jetzt am Ende von weg
	//weg hat Zielkreuzung 
	//benutze pZufaelligerWeg() in Zielkreuzung, um das Fahrzeug fahrend auf einen anderen Weg zu setzen.
	//Benutze vAnnahme um das Fahrzeug auf dem neuen Weg zu setzen

	Weg& neuWeg = this->p_pWeg.getZielKreuzung().pZufaelligerWeg(this->p_pWeg);	// zufaelliger Weg

	std::cout << "ZEIT : [" << dGlobaleZeit << " ]" << std::endl;
	std::cout << "KREUZUNG  :[ " << this->p_pWeg.getZielKreuzung().getName() << "] [ " << this->p_pWeg.getZielKreuzung().getTank() << " ]" << std::endl;
	std::cout << "WECHSEL:   [" << this->p_pWeg.getName() << " --->   " << neuWeg.getName() << " ]" << std::endl;
	std::cout << "FAHRZEUG : [" << this->p_pFahrzeug << " ]" << std::endl;

	this->p_pWeg.getZielKreuzung().vTanken(this->p_pFahrzeug);	//tanken von Fahrzeug durch die Ziel-Kreuzung von vorherigem Weg
	
	//unique_ptr<Fahrzeug> p_pFahrzeugAmEnde = p_pWeg.pAbgabe(this->p_pFahrzeug);  
	

	//pAbgabe deletes the car from list of Fahrzeuge and returns a unique_ptr<Fahrzeug>...then vAnnahme takes the unique_ptr<Fahrzeug> 
	// 
	//pAbgabe loescht das Fahrzeug von Liste und gibt ein unique_ptr<Fahrzeug> zurueck... dann vAnnahme nimmt unique_ptr<Fahrzeug> und setzt das Fahrzeug fahrend auf den neuen Weg
	neuWeg.vAnnahme(p_pWeg.pAbgabe(this->p_pFahrzeug));		
}