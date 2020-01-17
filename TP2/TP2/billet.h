/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#ifndef BILLET_H
#define BILLET_H

#include <string>
#include <iostream>
#include <iomanip>

#include "def.h"

using namespace std;

class Billet {
public:
	// Constructeurs
	Billet();
	Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol);

	~Billet();

	// Getters
	string getPnr() const;
	string getNomPassager() const;
	double getPrix() const;
	string getOd() const;
	TarifBillet getTarif() const;
	string getDateVol() const;

	// Setters
	void setPnr(const string& pnr);
	void setNomPassager(const string& nomPassager);
	void setPrix(double prix);
	void setOd(const string& od);
	void setTarif(TarifBillet tarif);
	void setDateVol(const string& dateVol);

	string formatTarif(TarifBillet tarif) const;

	// TODO: Remplacer cette methode par l'operateur <<
	friend ostream& operator << (ostream& os, const Billet& billet);
private:
	string pnr_;
	string nomPassager_;
	double prix_;
	string od_;
	TarifBillet tarif_;
	string dateVol_;
};
#endif // !BILLET_H

