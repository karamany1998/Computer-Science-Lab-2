#pragma once

#include "Simulationsobjekt.h"
#include "SimuClient.h"

#include <iostream>
#include <limits>
#include <string>
#include "Weg.h"

class Verhalten;

using namespace std;


//extern double dGlobaleZeit;


class Fahrzeug : public Simulationsobjekt
{
	
	private:
		
		protected:
		//const int p_iID;
		//string p_sName;
		double p_dMaxGeschwindigkeit;
		double p_dGesamtStrecke;
		double p_dGesamtZeit;

		unique_ptr<Verhalten> p_pVerhalten;
		//double p_dZeit;

		double p_dAbschnittStrecke;


	public:
		//static double dGlobaleZeit; //check time
		static int p_iMaxID;	//static variable of class Fahrzeug - increases by 1 everytime a constructor is called

		Fahrzeug();				//Default Constructor
		Fahrzeug(string name);  //constructor that initializes the name of the Fahrzeug class
		Fahrzeug(string name, double maxSpeed);  //constructor that initializes name and maxSpeed


		//verbieten von copy constructor 
		Fahrzeug(const Fahrzeug&) = delete;


		~Fahrzeug();//destructor

		static void vKopf();


		//virtual functions
		virtual double dTanken(double dMenge = numeric_limits<double>::infinity());
		virtual void vAusgeben(ostream& ) const;
		virtual void vSimulieren();
		virtual double dGeschwindigkeit() const;


		bool operator<(Fahrzeug& x);
		Fahrzeug& operator= (const Fahrzeug& x);


		void vNeueStrecke(Weg& weg);
		void vNeueStrecke(Weg& weg, double startZeit);

		virtual void vZeichnen(Weg&);



		//Getters

		double getAbschnitt()
		{
			return this->p_dAbschnittStrecke;
		}



		string getName();

	

};

