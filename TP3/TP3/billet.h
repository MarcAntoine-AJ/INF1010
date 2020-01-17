/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe C�T�-MORNEAULT
 */

#ifndef BILLET_H
#define BILLET_H

#include <string>
#include <iostream>
#include <iomanip>

#include "def.h"

using namespace std;

enum TypeBillet { Billet_Base, Billet_Regulier, Flight_Pass };

class Billet {
public:
	// Constructeurs
	//� modifier
	Billet();
	//� modifier
	Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet);

	virtual ~Billet(); //virtual permet de bien delete les object deriv� 

	// Getters
	string getPnr() const;
	string getNomPassager() const;
	double getPrix() const;
	string getOd() const;
	TarifBillet getTarif() const;

	//� faire
	TypeBillet getTypeBillet() const;

	// Setters
	void setPnr(const string& pnr);
	void setNomPassager(const string& nomPassager);
	void setPrix(double prix);
	void setOd(const string& od);
	void setTarif(TarifBillet tarif);
	//� faire
	void setTypeBillet(TypeBillet typeBillet);

	string formatTarif(TarifBillet tarif) const;

	//� modifer
	friend ostream& operator<<(ostream& o, const Billet& billet);
private:
	string pnr_;
	string nomPassager_;
	double prix_;
	string od_;
	TarifBillet tarif_;
	TypeBillet typeBillet_;
};
#endif // !BILLET_H

