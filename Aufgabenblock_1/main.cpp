

#include <iostream>
#include <string>
#include "Fahrzeug.h"
#include <memory>
#include <vector>
#include "PKW.h"
#include "Fahrrad.h"
#include <cmath>


double dEpsilon = 0.001;
double dGlobaleZeit;

using namespace std;


ostream& operator<<(ostream& os, Fahrzeug& vehicle)
{
	vehicle.vAusgeben(os);

	return os;
}




void vAufgabe_1()
{
	Fahrzeug f1("Car1");
	Fahrzeug f2("Car2");

	Fahrzeug* f3 = new Fahrzeug("Car3");


	unique_ptr<Fahrzeug> unique1 = make_unique<Fahrzeug>("Unique Pointer - Car1");
	unique_ptr<Fahrzeug> unique2 = make_unique<Fahrzeug>("Unique Pointer - Car2");

	shared_ptr<Fahrzeug> shared1 = make_shared<Fahrzeug>("Shared Pointer - Car1");
	cout << "Shared pointer points " << shared1.use_count() << " objects" << endl;

	shared_ptr<Fahrzeug> shared2 = make_shared<Fahrzeug>("Shared Pointer - Car2");
	cout << "Shared pointer points " << shared2.use_count() << " objects" << endl;

	shared_ptr<Fahrzeug> shared3 = shared2;					
	cout << "Shared pointer points to " << shared2.use_count() << " objects" << endl;		//output is 2 because shared2 and shared3 point to the same object on heap



	cout << "Unique pointer Vector: " << endl;
	vector<unique_ptr<Fahrzeug>> vecUnique;			
	vecUnique.push_back(std::move(unique1));		//we have to use std::move because only one pointer can have ownership of the object on heap
	vecUnique.push_back(std::move(unique2));		//this means that the pointers in vec1 now have ownership of these objects and not unique1 and unique2

	vecUnique.clear();


	cout << "------------------------------------" << endl;

	cout << "Shared pointer Vector: " << endl;
	vector<shared_ptr<Fahrzeug>> vecShared;
	vecShared.push_back(std::move(shared1));
	vecShared.push_back(shared2);

	cout << "Anzahl der Referenzen fuer die Elemente des Shared-Vectors" << endl;
	for (auto &p : vecShared)
	{
		cout << p.use_count() << endl;
	}

	cout << "------------------------------------" << endl;
	delete f3;

}


void vAufgabe_1a()
{

	vector< unique_ptr<Fahrzeug>> vecUnique;
	vecUnique.push_back(make_unique<Fahrzeug>("PKW", 35));
	vecUnique.push_back(make_unique<Fahrzeug>("DAS AUTO", 75));
	vecUnique.push_back(make_unique<Fahrzeug>("Dodge", 300));

	Fahrzeug::vKopf();
	double dsimulationZeit = 10;
	double dZeitTakt = 1;
	double dTime = 0; 
	while( fabs(dsimulationZeit - dTime) > dEpsilon)		//simulations ueber 10 Stunden
	{
		
		
		dGlobaleZeit = dTime;
		for (auto& p : vecUnique)
		{
			cout << *p << endl;

		}
		for (auto& p : vecUnique)
		{
			p->vSimulieren();
		}
		dTime += dZeitTakt;
	}

}



void vAufgabe_2()
{
	vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
	int anzahlPKW;
	cout << "Bitte Geben Sie die Anzahl der gewunschte PKW ein: ";
	cin >> anzahlPKW;

	for (int i = 0; i < anzahlPKW; i++)
	{
		string name;
		double maxSpeed;
		double volumen;
		double verbrauch;

		cout << "Bitte geben sie die Name, maximale Geschwindigkeit, verbrauch und Volumen des Tank Ihrers PKW an :" << endl;
		cout<< "<<-1 bedeuted, dass Sie keinen Wert fuer Volumen angeben und Default(55l) wird fuer Ihr PKW" << endl;

		cout << "Name :";
		cin >> name;
		cout << endl;

		cout << "Max Speed: ";
		cin >> maxSpeed;
		cout << endl;

		cout << "Verbrauch: ";
		cin >> verbrauch;
		cout << endl;

		cout << "Volumen ";
		cin >> volumen;
		
		if (volumen != -1)
		{
			//PKW pkw{name , maxSpeed , verbrauch };
			vecFahrzeuge.push_back(make_unique<PKW>(name , maxSpeed , verbrauch , volumen));
		}
		
		else
		{
			PKW pkw{ name , maxSpeed , verbrauch , volumen };
			vecFahrzeuge.push_back(make_unique<PKW>(name, maxSpeed, verbrauch));
		}
		cout << "----------------------------------------------------" << endl;
		
	}

	int anzahlFahrrad;
	cout << "Bitte Geben Sie die Anzahl der gewunschte Fahrraeder ein: ";
	cin >> anzahlFahrrad;

	for (int i = 0; i < anzahlFahrrad; i++)
	{
		string name; 
		double maxSpeed;

		cout << "bitte geben sie die Name und maximale Geschwindigkeit vom Fahrrad ein: " << endl;

		cout << "Name :";
		cin >> name;
		cout << endl;

		cout << "max Speed: ";
		cin >> maxSpeed;
		cout << endl;

		vecFahrzeuge.push_back(make_unique<Fahrrad>(name, maxSpeed));
	}


	double timeSimulation = 0; 
	double zeitTakt = 0; 
	cout << "Wie lange soll die gesamte Simulation Zeit dauern(in Studen)?" << endl;
	cout << "Simulation time : ";
	cin >> timeSimulation;
	cout << endl;

	cout << "Wie lange soll jede Simulationsschritt dauern(in Stunden)?" << endl;
	cout << "Zeit Takt: ";
	cin >> zeitTakt;


	cout << endl;


	double x = 0; 

	
	Fahrzeug::vKopf();

	for (double t = 0; abs(t-timeSimulation)>dEpsilon; t += zeitTakt)
	{
		cout << "Zustand der Fahrzeuge nach " << t << " Studenden" << endl;
		for (auto& p : vecFahrzeuge)		//Update vehicles after each time interval
		{
			int divTime = (int)t;  //Approximation von Zeit durch 

			double isDivisible = fmod(t, 3);
			if (isDivisible <= dEpsilon && t!=0)  //check if 3 hours passed to tank PKW
			{
				cout << "You need to tank this PKW:" << endl;
				cout << "How many liters do you want to tank , (-1)=Full Tank" << endl;
				double tank;
				cout << "Tankmenge: ";
				cin >> tank;
				cout << endl;

				p->dTanken(tank);// if 3 hours pass, then tank PKW
			}
			
			p->vSimulieren();
			cout << *p;
			cout << endl;
		}
		x += zeitTakt;

		dGlobaleZeit = t;
		cout << "--------------------------------------------------------------" << endl;
	}
	




	cout << endl;


}






void vAufgabe_3()
{


	cout << " Ueberladen von << Operator" << endl;
	Fahrzeug* pkw1 = new PKW("Mohamed_PKW", 35, 50, 100);

	Fahrzeug* fahrrad1 = new Fahrrad("BMX9000", 90);

	cout << *pkw1 << endl;
	cout << *fahrrad1 << endl;


	delete pkw1;
	delete fahrrad1;

	
	cout << "===============================================================" << endl;

	Fahrzeug* myCar = new PKW("Mohamed_PKW", 35, 60, 55);
	cout << *myCar << endl;
	cout << "-============================================-" << endl;




	cout << " Ueberladen von =(zuweisung) Operator" << endl;

	Fahrzeug* gokuCar = new PKW("Goku_Kamehameha", 35, 55);
	*gokuCar = *myCar;
	cout << "=========================================" << endl;
	cout << *gokuCar << endl;
	cout << *gokuCar << endl;


	cout << "--------------------------------------------------------" << endl;

	cout << "Check <-Operator" << endl;
	Fahrzeug* fastCar = new PKW("Fast_PKW", 100, 55);
	Fahrzeug* slowCar = new PKW("Slow_PKW", 20, 55);
	dGlobaleZeit = 3;


	fastCar->vSimulieren();
	slowCar->vSimulieren();

	Fahrzeug::vKopf();
	cout<<endl;
	cout << *fastCar << endl;
	cout << *slowCar << endl;

	if (*slowCar < *fastCar)
	{
		cout << "Slow car is really slow" << endl;
	}
	else
	{
		cout << "fast car is really fast" << endl;
	}



	delete fastCar;
	delete slowCar;
	

}


void vAufgabe_Probe() {
	Fahrzeug* pF1 = new PKW("Audi", 150, 8);
	dGlobaleZeit = 0.0;
	Fahrzeug::vKopf();
	dGlobaleZeit = 3.0;
	cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
	pF1->vSimulieren();
	std::cout << *pF1 << endl;
	delete pF1;
	char c;
	std::cin >> c;
}


void vAufgabe_AB1() {

	int l = 0; // Laufindex für gezielte AUsgabe
	vector<int> ausgabe{ 15 };
	double dTakt = 0.3;

	std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
	vecFahrzeuge.push_back(make_unique <PKW>("Audi", 231, 11.4));
	vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 19.8));
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
	{
		auto itL = find(ausgabe.begin(), ausgabe.end(), l);
		if (itL != ausgabe.end()) {
			std::cout << std::endl << l << " Globalezeit = " << dGlobaleZeit << std::endl;
			Fahrzeug::vKopf();
		}

		for (int i = 0; i < vecFahrzeuge.size(); i++)
		{
			vecFahrzeuge[i]->vSimulieren();
			if (fabs(dGlobaleZeit - 3.0) < dTakt / 2)
			{
				vecFahrzeuge[i]->dTanken();
			}
			if (itL != ausgabe.end()) {
				std::cout << *vecFahrzeuge[i] << endl;
			}
		}
		l++;
	}
	char c;
	std::cin >> c;
}



int main()
{
	


	//vAufgabe_1();

	//vAufgabe_1a();
	

	//vAufgabe_2();

	
	//vAufgabe_3();


	//vAufgabe_Probe();
	
	//vAufgabe_AB1();


	Fahrzeug* ptr1 = new<Fahrzeug>("Audi", 140);
	return 0;

}