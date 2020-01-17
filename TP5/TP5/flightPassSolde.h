/********************************************
* Titre: Travail pratique #5 - flightPassSolde.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef FLIGHT_PASS_SOLDE_H
#define FLIGHT_PASS_SOLDE_H

#include <iomanip>

#include "flightPass.h"
#include "solde.h"

using namespace std;

class FlightPassSolde : public FlightPass, public Solde {
public:
	// Constructeur
	FlightPassSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, double pourcentageSolde);

	// Getter
	double getPrix() const override;
	double getPrixBase() const override;

	FlightPassSolde* clone() const override;

	void afficher(ostream& o) const override;
};
#endif // !FLIGHT_PASS_SOLDE_H
