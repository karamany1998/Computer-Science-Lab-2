

#include <iostream>
#include <fstream>
#include <string>
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include <memory>
#include <vector>
#include "PKW.h"
#include "Fahrrad.h"
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Weg.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "vertagt_aktion.h"
#include <cmath>
#include <random>
#include "Kreuzung.h"
#include "Simulation.h"


double dEpsilon = 0.001;
double dGlobaleZeit;

using namespace std;

ostream& operator<<(ostream& os, Simulationsobjekt& objekt)
{
	objekt.vAusgeben(os);

	return os;
}

istream& operator>>(istream& is, Simulationsobjekt& objekt)
{
	objekt.vEinlesen(is);
	return is;
}





bool operator==(const Simulationsobjekt& lhs, const Simulationsobjekt& rhs)
{
	if (lhs.p_iMaxID == rhs.p_iMaxID)return true;
	else return false;
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





/*
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
*/


/*
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
*/


/*
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

*/

/*
void vAufgabe_4()
{
	Weg* weg1 = new Weg("Haputstrasse", 50, Tempolimit::Innerorts);

	weg1->vKopf();
	cout << endl;
	cout << *weg1 << endl;


}
*/

/*
void vAufgabe_5()
{

	
	Weg weg("Haputstrasse", 350, Tempolimit::Landstrasse);  //350km lang strasse mit 100km Tempolimit
	weg.vKopf();
	cout << endl;
	cout << weg << endl << endl;

	//3 Fahrzeuge
	unique_ptr<Fahrzeug> ptr1 = make_unique<Fahrzeug>("Jaguar", 60);
	unique_ptr<Fahrzeug> ptr2 = make_unique<Fahrzeug>("Audi", 30);
	unique_ptr<Fahrzeug> ptr3 = make_unique<Fahrzeug>("BMX", 15);
	unique_ptr<Fahrzeug> ptr4 = make_unique<Fahrzeug>("Toyota", 15);

	//addiere 3 Fahrzeuge in Weg
	weg.vAnnahme(std::move(ptr1));
	weg.vAnnahme(std::move(ptr2));
	weg.vAnnahme(std::move(ptr3));
	weg.vAnnahme(std::move(ptr4) , 2);

	cout << endl << endl;
	cout << "Erste Simulation und Aktualisieren ..." << endl;
	weg.vSimulieren();
	cout << endl << endl;
	weg.vKopf();
	cout << endl;
	cout << weg << endl; 

	cout << "---------------------------------------------" << endl << endl;
	double dt = 0.5;
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dt) {
		try
		{
			weg.vSimulieren();
			cout << "Zeit :" << dGlobaleZeit << endl;
			cout << weg << endl;
		}
		catch (Fahrausnahme& ex)
		{
			ex.vBearbeiten();
		}
	}
	

	cout << "---------------------------------------------" << endl << endl;
	weg.vKopf();
	cout << endl;
	cout << weg << endl;

}
*/


void vAufgabe_6()
{
	bInitialisiereGrafik(1200, 1200);
	vSetzeZeit(dGlobaleZeit);
	
	Weg wegOhneTempo("Hauptst", 100);
	unique_ptr<Fahrzeug> Fzg1 = make_unique<Fahrrad>("AUDI", 100);	//fahrendes Fahrzeug
	unique_ptr<Fahrzeug> Fzg2 = make_unique<PKW>("LADA", 50, 20, 100);	//fahrendes Fahrzeug
	unique_ptr<Fahrzeug> Fzg3 = make_unique<PKW>("Toyota", 25, 10, 150);	//parkendes Fahrzeug, start ab 3
	unique_ptr<Fahrzeug> Fzg4 = make_unique<PKW>("Corolla", 75, 100, 200);	//parkendes Fahrzeug, start ab 5.5
	unique_ptr<Fahrzeug> Fzg5 = make_unique<PKW>("Challenger", 30, 100, 20);	//parkendes Fahrzeug, start ab 5.5
	
	int koordinateStrasse[4] = { 200 , 200 , 200 , 300 };
	bZeichneStrasse("Hauptst", "Ruckst", 100, 2, koordinateStrasse);

	wegOhneTempo.vAnnahme(move(Fzg1));
	wegOhneTempo.vAnnahme(move(Fzg2));
	wegOhneTempo.vAnnahme(move(Fzg3) , 3);
	


	Weg wegMitTempo("MyStreet", 300, Tempolimit::Landstrasse);  //Ein Landstrasse (name = MyStreet, length = 300km , Tempolimit = 100);
	unique_ptr<Fahrzeug> bike1 = make_unique<Fahrrad>("MyBike", 100);	//fahrendes Fahrzeug
	unique_ptr<Fahrzeug> car1 = make_unique<PKW>("Armada", 50, 20, 100);	//fahrendes Fahrzeug
	unique_ptr<Fahrzeug> car2 = make_unique<PKW>("Toyota", 150, 10, 150);	//parkendes Fahrzeug, start ab 3
	unique_ptr<Fahrzeug> car3 = make_unique<PKW>("Corolla", 200, 5, 200);	//parkendes Fahrzeug, start ab 5.5
	unique_ptr<Fahrzeug> car4 = make_unique<PKW>("Challenger", 200, 5, 200);	//fahrendes Fahrzeug

	
	wegMitTempo.vAnnahme(move(bike1));
	wegMitTempo.vAnnahme(move(car1));
	wegMitTempo.vAnnahme(move(car2) , 3);
	wegMitTempo.vAnnahme(move(car3) , 5.5);
	wegMitTempo.vAnnahme(move(car4));


	
	int koordinateStrasse3[4] = { 800 , 500 , 500 , 500 };
	bZeichneStrasse("MyStreet", "returnStr", 300, 2, koordinateStrasse3);


	//Weg wegMitTempo("NebenStr", 100, Tempolimit::Landstrasse);

	

	/*
	int koordinateStrasse2[4] = { 700 , 250 , 200 , 250 };
	Weg myStreet("main_st", 500);	//default soll Tempolimit::Autobahn sein
	bZeichneStrasse("main_st", "side_st", 500, 2, koordinateStrasse2);
	myStreet.vAnnahme(move(Fzg1));
	myStreet.vAnnahme(move(Fzg2));
	myStreet.vAnnahme(move(Fzg4) , 5.5); 
	*/

	vSetzeZeit(dGlobaleZeit);

	cout << "WEG" << endl;
	cout << wegMitTempo << endl;

	double dTakt = 0.25;
	for (dGlobaleZeit = 0; dGlobaleZeit < 25; dGlobaleZeit += dTakt)
	{
		
			wegMitTempo.vSimulieren();
			wegOhneTempo.vSimulieren();
			vSleep(100);
			vSetzeZeit(dGlobaleZeit);
	}

	cout << wegMitTempo << endl;


	vBeendeGrafik();

}




void vAufgabe_6a()
{

	
	//using namespace vertagt;

	class vertagt::VListe<int> intList;


	cout << "ADD numbers between 1 and 10 in VListe..." << endl;
	for (int i = 1; i <= 10; i++)
	{
		if (i % 2)
		{
			intList.push_front(i);
			intList.push_front(i);
		}
		else
		{
			intList.push_back(i);
			intList.push_back(i);
		}
			
	}

	cout << "Aktualisieren... " << endl;
	intList.vAktualisieren();


	cout << "Printing ...." << endl;
	for (list<int>::iterator it = intList.begin(); it != intList.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "-------------------------------------------------------------------" << endl;

	cout << "Deleted all elements greater than 5, but no Aktualisieren" << endl;
	for (list<int>::iterator it = intList.begin(); it != intList.end(); it++)
	{
		if (*it > 5)
		{
			intList.erase(it);
		}
	}

	cout << endl;


	
	cout << "Printing ...." << endl;
	for (list<int>::iterator it = intList.begin(); it != intList.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	cout << "Aktualisieren..." << endl;
	intList.vAktualisieren();

	cout << "Printing ...." << endl;
	for (list<int>::iterator it = intList.begin(); it != intList.end(); it++)
	{
		cout << *it << " ";
	}


	cout << endl;
	//random int in Liste einfuegen

	
	static std::mt19937 device(0);
	

	
	cout << "Adding two random numbers between a and b";
	int a;
	int b;
	cout << endl;

	cout << "Please input number a: ";
	cin >> a;
	cout << endl;
	cout << "Please input number b: ";
	cin >> b;

	std::uniform_int_distribution<int> dist(a, b);		//choose random numbers between a=5 and b=500

	int zuf = dist(device);
	int zuf2 = dist(device);
	intList.push_front(zuf);
	intList.push_back(zuf2);



	cout << "Printing ...." << endl;
	for (list<int>::iterator it = intList.begin(); it != intList.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	cout << "Aktualisieren..." << endl;
	intList.vAktualisieren();

	cout << "Printing ...." << endl;
	for (list<int>::iterator it = intList.begin(); it != intList.end(); it++)
	{
		cout << *it << " ";
	}

	


}


void AufgabeQ6()
{
	auto pPKW = make_unique<PKW>("BMW", 150);
	Weg aStr("Strasse", 500);
	aStr.vAnnahme(move(pPKW));

	dGlobaleZeit = 0;
	for (dGlobaleZeit = 0; dGlobaleZeit <= 6; dGlobaleZeit++)
	{
		aStr.vSimulieren();
	}

}

void AufgabeQ1()
{
	auto pPKW = make_unique<PKW>("BMW", 150 , 5 , 500);
	Weg aStr("Strasse", 500);
	aStr.vAnnahme(move(pPKW) , 3);
	
	for (dGlobaleZeit = 0; dGlobaleZeit <= 6; dGlobaleZeit+=0.2)
	{
		try
		{
			aStr.vSimulieren();
		}
		catch (...)
		{
			cout << "Zeit: " << dGlobaleZeit << endl;

		}

	}
	
}



void vAufgabe_7() {

	bInitialisiereGrafik(1200, 1200);
	vSetzeZeit(dGlobaleZeit);


	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	//strasse1 von (680,40) zu (680,300)
	int koordinateStrasse1[4] = { 680 , 40 , 680 , 300 };
	bZeichneStrasse("W12", "W21", 40, 2, koordinateStrasse1);

	//strasse2 =   (680,300) -> (850, 300) -> (970 , 390) -> (970, 500) -> (850,570)-> (680, 570)
	int koordinateStrasse2[12] = { 680 , 300 , 850, 300 , 970 , 390 , 970, 500 , 850,570 , 680, 570 };
	bZeichneStrasse("W23a", "W32a", 115, 6, koordinateStrasse2);

	//strasse3 = (680, 300) -> (680,570)
	int koordinateStrasse3[4] = { 680, 300 , 680,570 };
	bZeichneStrasse("W23b", "W32b", 40, 2, koordinateStrasse3);

	//strasse4 = (680,300) -> (320 , 300)
	int koordinateStrasse4[4] = { 680,300 , 320 , 300 };
	bZeichneStrasse("W24", "W42", 55, 2, koordinateStrasse4);

	//strasse5 = (680 , 570) , (500,570), (350,510) , (320, 420) , (320, 300)
	int koordinateStrasse5[10] = { 680 , 570 , 500,570, 350,510 , 320, 420 , 320, 300 };
	bZeichneStrasse("W34", "W43", 85, 5, koordinateStrasse5);

	//strasse6 = (320, 300) , (170, 300) , (70,250) , (80,90) , (200,60) , (320 , 150) , (320, 300)
	int koordinateStrasse6[14] = { 320, 300, 170, 300 , 70,250 , 80,90 , 200,60 , 320 , 150 , 320, 300 };
	bZeichneStrasse("W44a", "W44b", 130, 7, koordinateStrasse6);




	//Weg(std::string name, double lang, bool UeberholVerbot, weak_ptr<Kreuzung> ziel, Tempolimit tempoLimit = Tempolimit::Autobahn);
	
	//Kreuzungen initializieren
	shared_ptr<Kreuzung> p_kr1 = make_shared<Kreuzung>("Kreuzung1");
	shared_ptr<Kreuzung> p_kr2 = make_shared<Kreuzung>("Kreuzung2", 10001);
	shared_ptr<Kreuzung> p_kr3 = make_shared<Kreuzung>("Kreuzung3");
	shared_ptr<Kreuzung> p_kr4 = make_shared<Kreuzung>("Kreuzung4");

	//Wege erzeugen und Kreuzungen verbinden
	Kreuzung::vVerbinde("W12", "W21", 40, p_kr1, p_kr2, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W23a", "W32a", 115, p_kr2, p_kr3,Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W23b", "W32b", 40, p_kr3, p_kr2, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W24", "W42", 55, p_kr2, p_kr4, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W34", "W43", 85, p_kr3, p_kr4, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W44a", "W44b", 130, p_kr4,  p_kr4, Tempolimit::Landstrasse, false);


	//Fahrzeuge auf erste Kreuzung annehmen
	//unique_ptr<Fahrzeug> ptr1 = make_unique<Fahrzeug>("Jaguar", 60);
	p_kr1->vAnnahme(make_unique<Fahrzeug>("Jaguar", 25) , 2);
	//p_kr1->vAnnahme(make_unique<Fahrrad>("MyBike", 25), 2);
	//p_kr1->vAnnahme(make_unique<PKW>("Armada", 50, 20, 100), 3);
	//p_kr1->vAnnahme(make_unique<PKW>("Toyota", 150, 10, 150), 4);
	//p_kr1->vAnnahme(make_unique<PKW>("Challenger", 200, 5, 200), 7);

	//---------------------------------------------------//
	//Simulation 
	double dTakt = 0.5;
	for (dGlobaleZeit = 0; dGlobaleZeit < 25; dGlobaleZeit += dTakt)
	{

		p_kr1->vSimulieren();
		p_kr2->vSimulieren();
		p_kr3->vSimulieren();
		p_kr4->vSimulieren();
		vSleep(100);
		vSetzeZeit(dGlobaleZeit);
	}

	vBeendeGrafik();

}


void vAufgabe_8()
{

	ifstream infile{ "VO.dat" };

	if (!infile)
	{
		std::cerr << "Error Opening Input File..." << endl;
		std::cerr << "Program Terminating..." << endl;
		return;
	}

	/*
	while (!infile.eof())	//works
	{
		string x;
		infile >> x;
		cout << x << endl;
	}

	return;
	*/

	Fahrrad bike1;
	Kreuzung crossing1;
	PKW toyota1;

	infile >> toyota1 >> bike1 >> crossing1;
	
	cout << "Die folgende Fahrzeuge sind im VO.dat " << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << toyota1 << endl;
	cout << bike1 << endl;
	cout << crossing1 << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;


}




void vAufgabe_9()
{

	ifstream infile{ "Simu.dat" };

	if (!infile)
	{
		std::cerr << "Error Opening Input File..." << endl;
		std::cerr << "Program Terminating..." << endl;
		return;
	}

	Simulation simulate;
	simulate.vEinlesen(infile);
	simulate.vSimulieren(10, 0.5);




}

void vAufgabe_9a()
{

	ifstream infile{ "SimuDisplay.dat" };

	if (!infile)
	{
		std::cerr << "Error Opening Input File..." << endl;
		std::cerr << "Program Terminating..." << endl;
		return;
	}

	Simulation simulate;
	simulate.vEinlesen(infile , true);
	simulate.vSimulieren(10, 0.2);


	vBeendeGrafik();


}




int main()
{
	


	//-------------------------------------------------------------------------------------------------------------//
	//------------------------------------------AUFGABENBLOCK 1----------------------------------------------------//

	//vAufgabe_1();

	//vAufgabe_1a();
	

	//vAufgabe_2();

	
	//vAufgabe_3();


	//vAufgabe_Probe();
	
	//vAufgabe_AB1();

	//Fahrzeug* ptr1 = new<Fahrzeug>("Audi", 140);





	//-------------------------------------------------------------------------------------------------------------//
	//------------------------------------------AUFGABENBLOCK 2----------------------------------------------------//

	//vAufgabe_4();



	//vAufgabe_5();

	

	//vAufgabe_6();



	//vAufgabe_6a();




	//----------------------------------------------------------------------------------------------------------------//
	// ---------------------------------------------------------------------------------------------------------------//
	//AufgabeQ6();
	//AufgabeQ1();



	//----------------------------------------------------------------------------------------------------------------//
	// ---------------------------------------------------------------------------------------------------------------//

	//PART 3 

	//vAufgabe_7();

	//vAufgabe_8();

	//vAufgabe_9();

	vAufgabe_9a();


	
	return 0;

}