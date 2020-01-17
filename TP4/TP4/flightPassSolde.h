/*
* Titre : flightPassSolde.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#ifndef FLIGHT_PASS_SOLDE_H
#define FLIGHT_PASS_SOLDE_H

#include <iomanip>

#include "flightPass.h"
#include "solde.h"

using namespace std;

class FlightPassSolde : public FlightPass, public Solde {
public:
	// Constructeur
	// TODO
	FlightPassSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, double pourcentageSolde);

	// Getter
	// TODO
	double getPrix() const  override; 
	double getPrixBase() override ;

	// TODO
	FlightPassSolde* clone() const  override;

	// TODO
	void afficher(ostream& o) const override;
};
#endif // !FLIGHT_PASS_SOLDE_H
