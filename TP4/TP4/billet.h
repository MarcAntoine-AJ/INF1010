/*
* Titre : billet.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#ifndef BILLET_H
#define BILLET_H

#include <string>
#include <iomanip>

#include "def.h"

using namespace std;

class Billet {
public:
	// Constructeurs
	Billet();
	Billet(const string& pnr, double prix, const string& od, TarifBillet tarif);

	virtual ~Billet();

	// Getters
	string getPnr() const;
	string getNomPassager() const;
	virtual double getPrix() const ;  
	string getOd() const;
	TarifBillet getTarif() const;

	// Setters
	void setPnr(const string& pnr);
	void setNomPassager(const string& nomPassager);
	void setPrix(double prix);
	void setOd(const string& od);
	void setTarif(TarifBillet tarif);

	string formatTarif(TarifBillet tarif) const;

	// TODO
	virtual Billet* clone() const =0;
	// TODO
	virtual void afficher(ostream& o) const ;
protected:
	string pnr_;
	string nomPassager_;
	double prix_;
	string od_;
	TarifBillet tarif_;
};
#endif // !BILLET_H