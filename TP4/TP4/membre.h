/*
* Titre : membre.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#ifndef MEMBRE_H
#define MEMBRE_H

#include <string>
#include <vector>
#include <iomanip>

#include "flightPass.h"
#include "billetRegulier.h"
#include "coupon.h"

using namespace std;

class Membre {
public:
	// Constructeurs
	Membre();
	Membre(const string& nom);
	// TODO
	Membre(const Membre& membre);

	virtual ~Membre();

	// Getters
	string getNom() const;

	vector<Billet*> getBillets() const;

	// Setters
	void setNom(const string& nom);
	
	// TODO
	void utiliserBillet(const string& pnr);
	virtual void ajouterBillet(Billet* billet);

	bool operator==(const string& nomMembre) const;
	friend bool operator==(const string& nomMembre, const Membre& membre);

	// TODO
	Membre& operator=(const Membre& membre);
	// TODO
	virtual void afficher(ostream& o) const ;
protected:
	string nom_;
	vector<Billet*> billets_;
};
#endif // !MEMBRE_H
