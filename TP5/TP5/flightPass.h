/********************************************
* Titre: Travail pratique #5 - flightPass.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef FLIGHT_PASS_H
#define FLIGHT_PASS_H

#include <iomanip>

#include "billet.h"

class FlightPass : public Billet {
public:
	FlightPass(const string& pnr, double prix, const string& od, TarifBillet tarif);

	int getNbUtilisationsRestante() const;

	void decrementeNbUtilisations();

	FlightPass* clone() const override;

	void afficher(ostream& o) const override;
private:
	int nbUtilisationsRestante_;
};
#endif // !FLIGHT_PASS_H