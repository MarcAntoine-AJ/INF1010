/*
* Titre : billetRegulier.h - Travail Pratique #3
* Date : 20 Septembre 2019
* Auteur : Jeffrey Lavallee
*/

#ifndef BILLET_REGULIER_H
#define BILLET_REGULIER_H
#include "billet.h"


class BilletRegulier : public Billet {

public:

	//� faire 
	BilletRegulier(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol, TypeBillet typeBillet);
	//� faire 
	string getDateVol() const;
	//� faire 
	void setDateVol(string dateVol);

	//� faire 
	friend ostream& operator<<(ostream& o, const BilletRegulier& billet);
private:
	string dateVol_;
};

#endif