#pragma once
#include <iostream>
#include <limits>
#include <string>
using namespace std;


extern double dGlobaleZeit;


class Fahrzeug
{
	
	private:
		
		
		
	protected:
		const int p_iID;
		string p_sName;
		double p_dMaxGeschwindigkeit;
		double p_dGesamtStrecke;
		double p_dGesamtZeit;
		double p_dZeit;


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


};

