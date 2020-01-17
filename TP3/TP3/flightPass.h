/*
* Titre : membrePremium.h - Travail Pratique #3
* Date : 20 Septembre 2019
* Auteur : Jeffrey Lavallee
*/

#ifndef FLIGHT_PASS_H
#define FLIGHT_PASS_H

#include "billet.h"

class FlightPass : public Billet {
public:
	//� faire 
	FlightPass(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet);

	//� faire 
	void decrementeNbUtilisations();

	//� faire 
	int getNbUtilisationsRestante() const;

	//� faire 
	friend ostream& operator<<(ostream& os, const FlightPass& flightpass);

private:
	int nbUtilisationsRestante_;
};

#endif