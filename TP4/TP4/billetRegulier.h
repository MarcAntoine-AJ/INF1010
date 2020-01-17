/*
* Titre : billetRegulier.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#ifndef BILLET_REGULIER_H
#define BILLET_REGULIER_H

#include <iomanip>

#include "billet.h"

class BilletRegulier : public Billet {

public:
	// Constructeur
	BilletRegulier(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol);

	// Getter
	string getDateVol() const;

	// Setter
	void setDateVol(string dateVol);

	// TODO
	BilletRegulier* clone() const override;
	// TODO
	void afficher(ostream& o) const override ;
private:
	string dateVol_;
};
#endif // !BILLET_REGULIER_H