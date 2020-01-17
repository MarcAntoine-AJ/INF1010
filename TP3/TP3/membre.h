/*
* Titre : membre.h - Travail Pratique #3
* Date : 20 Septembre 2019
* Auteur : Jeffrey Lavallee
*/


#ifndef MEMBRE_H
#define MEMBRE_H

#include <string>
#include <vector>

#include "flightPass.h"
#include "billetRegulier.h"
#include "coupon.h"

using namespace std;

enum TypeMembre { Membre_Regulier, Membre_Premium, Membre_Occasionnel };

class Membre {
public:
	// Constructeurs

	//à modifer
	Membre();
	//à modifer
	Membre(const string& nom, TypeMembre typeMembre);
	//à modifer
	Membre(const Membre& membre);

	virtual ~Membre(); //virtual permet de bien delete les object derivé 

	// Getters
	string getNom() const;
	TypeMembre getTypeMembre() const;

	vector<Billet*> getBillets() const;


	// Setters
	void setNom(const string& nom);

	//à faire
	void utiliserBillet(const string& pnr);

	//à modifer
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol);

	bool operator==(const string& nomMembre) const;
	friend bool operator==(const string& nomMembre, const Membre& membre);

	Membre& operator=(const Membre& membre);

	//à modifer
	friend ostream& operator<<(ostream& o, const Membre& membre);
protected:
	string nom_;
	TypeMembre typeMembre_;
	vector<Billet*> billets_;
};


#endif
