#include "Simulation.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Tempolimit.h"
#include "Simulationsobjekt.h"



//Changes to Simu.dat
/*
Errors sind an Zeilen -> 3 , 11 , 12 , 13 

Zeile3: Kr3 ist unbekannt --> swtich Zeile3 and Zeile4
Zeile11 : Unbekanntes Schluesselwort -->delete Zeiel

Zeile 12: Kreuzung(Error) nicht gefunden -- > change to Kreuzung(1) oder andere bel. Kreuzung
Zeile 13 : Kreuzung(Mercedes) nicht gefunden --> change to Kreuzung(2)



*/



void Simulation::vEinlesen(istream& eingabe , bool bMitGrafik )
{
	int zeilenNummer = 1; 

	//set Grafik
	if (bMitGrafik)
	{
		bInitialisiereGrafik(1200, 1200);
		vSetzeZeit(dGlobaleZeit);
	}

	while (eingabe.good()) //lese bis wir fertig mit dem Eingabefile sind
	{
		string schlusselwort;	//entscheide welches objekt erzeugt wird
		eingabe >> schlusselwort;


		//Erzeuge Kreuzung
		if (schlusselwort == "KREUZUNG")
		{
			//Kreuzung kr;
			//is >> kr;

			//Kreuzung* kr = new Kreuzung();
			shared_ptr<Kreuzung> p_kr;
			p_kr = make_shared<Kreuzung>();
			eingabe >> *p_kr;
			int xPos, yPos; //x, y coordinates of Kreuzung(nur mit bMitGrafik)

			try
			{
				if (mapToSimulationObject.find(p_kr->getName()) != mapToSimulationObject.end())	//name bereits im Map gespeichert --> throw runtime error
				{
					throw runtime_error("Error an Zeile: " +to_string(zeilenNummer)+ " eine Kreuzung mit diesem Name wurde bereits eingegeben");
				}
				mapToSimulationObject[p_kr->getName()] = p_kr;

				if (bMitGrafik)
				{
					eingabe >> xPos >> yPos;
					bZeichneKreuzung(xPos, yPos);
				}
			}

			catch (std::runtime_error& ex)
			{
				cerr << ex.what() << endl;
			}
		}
		else if (schlusselwort == "PKW")
		{
			unique_ptr<PKW> car = make_unique<PKW>();
			eingabe >> *car;

			string nameKreuzung;	
			eingabe >> nameKreuzung;
			try
			{
				if (mapToSimulationObject.find(nameKreuzung) == mapToSimulationObject.end())
				{
					throw runtime_error("Error an Zeile " + to_string(zeilenNummer) + " Das Programm findet nicht die Kreuzung : " + nameKreuzung);
				}

				double zeitLosFahren;
				eingabe >> zeitLosFahren;

				mapToSimulationObject[nameKreuzung]->vAnnahme(move(car), zeitLosFahren);
			}
			catch (std::runtime_error& ex)
			{
				cerr << ex.what() << endl;
			}
		}
		else if (schlusselwort == "FAHRRAD")
		{
			//Fahrrad bike;
			//eingabe >> bike;

			unique_ptr<Fahrrad> bike = make_unique<Fahrrad>();
			eingabe >> *bike;

			string nameKreuzung;
			eingabe >> nameKreuzung;
			try
			{
				if (mapToSimulationObject.find(nameKreuzung) == mapToSimulationObject.end())
				{
					throw runtime_error("Error an Zeile " +to_string(zeilenNummer)+ " Das Programm findet nicht die Kreuzung : " + nameKreuzung);
				}
				double zeitLosFahren;
				eingabe >> zeitLosFahren;

				mapToSimulationObject[nameKreuzung]->vAnnahme(move(bike), zeitLosFahren);
			}
			catch (std::runtime_error& ex)
			{
				cerr << ex.what() << endl;
			}

			

		}
		else if (schlusselwort == "STRASSE")
		{
			string quell_kr;
			string ziel_kr;
			string hinWeg;
			string ruckWeg;
			int laenge;
			int speed;
			Tempolimit speedLimit;
			bool Ueberholverbot;

			int anzahlKoordinate;

			eingabe >> quell_kr >> ziel_kr >> hinWeg >> ruckWeg >> laenge >> speed >> Ueberholverbot;
			speedLimit = (Tempolimit)speed;

			//uerbpruefe, dass Kreuzungen im Map zu finden sind.

			try
			{
				if (mapToSimulationObject.find(quell_kr) == mapToSimulationObject.end())
				{
					//ERROR
					throw runtime_error("Error an Zeile " + to_string(zeilenNummer) + " Das Programm findet nicht die Kreuzung : " + quell_kr);
				}
				if (mapToSimulationObject.find(ziel_kr) == mapToSimulationObject.end())
				{
					throw runtime_error("Error an Zeile " + to_string(zeilenNummer) + " Das Programm findet nicht die Kreuzung : " + ziel_kr);
				}
				Kreuzung::vVerbinde(hinWeg, ruckWeg, laenge, mapToSimulationObject[quell_kr], mapToSimulationObject[ziel_kr], speedLimit, Ueberholverbot);

				
				if (bMitGrafik)
				{
					eingabe >> anzahlKoordinate;
					int* koordinate = new int[anzahlKoordinate * 2];
					for (int i = 0; i < 2*anzahlKoordinate; i++)
					{	
						eingabe >> koordinate[i];
						
					}
					bZeichneStrasse(hinWeg, ruckWeg, laenge, anzahlKoordinate, koordinate);

				}
				
			}
				
			catch (std::runtime_error& ex)
			{
				cerr << ex.what() << endl;
			}
		}
		else
		{
			//ERROR
			try
			{
				throw runtime_error("Error an Zeile " + to_string(zeilenNummer) + "Sie haben ein unbekanntes Schlusselwort eingegeben...");
			}
			catch (std::runtime_error& ex)
			{
				cerr << ex.what() << endl;
			}


		}
		
		//falls kein Fehler auftriit
		zeilenNummer++;
		
	}
	
}



//Simulate each Kreuzung
void Simulation::vSimulieren()
{
	for (auto& key_val : this->mapToSimulationObject)
	{
		key_val.second->vSimulieren(); // simuliere jede Kreuzung
		//vSleep(10);
		vSetzeZeit(dGlobaleZeit);
	}

}



void Simulation::vSimulieren(double dDauer , double dZeitSchritt)
{
	for (dGlobaleZeit = 0; dGlobaleZeit <= dDauer; dGlobaleZeit += dZeitSchritt)
	{
		Simulation::vSimulieren();
		
	}
}