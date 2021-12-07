#pragma once


#include <iostream>
#include <limits>
#include <string>
using namespace std;

extern double dGlobaleZeit;





class Simulationsobjekt
{

protected:

	const int p_iID;
	string p_sName;
	double p_dZeit;


public:

	virtual void vAusgeben(ostream&) const;
	virtual void vSimulieren() = 0;

	static int p_iMaxID;


	Simulationsobjekt();
	Simulationsobjekt(string name);
	~Simulationsobjekt();

	Simulationsobjekt(const Simulationsobjekt&) = delete;

	void setStartTime(double);
	





};


ostream& operator<<(ostream& os, Simulationsobjekt& objekt);


bool operator==(const Simulationsobjekt& lhs, const Simulationsobjekt& rhs);