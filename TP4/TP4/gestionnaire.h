/*
* Titre : gestionnaire.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#ifndef GESTIONNAIRE_H
#define	GESTIONNAIRE_H

#include <vector>

#include "membrePremium.h"
#include "solde.h"
#include "debogageMemoire.hpp"

class Gestionnaire {
public:
	// Constructeur
	Gestionnaire();

	~Gestionnaire();

	// Getters
	vector<Membre*> getMembres() const;
	vector<Coupon*> getCoupons() const;

	void ajouterMembre(Membre* membre);
	void ajouterCoupon(Coupon* coupon);

	Membre* trouverMembre(const string& nomMembre) const;
	// TODO
	void assignerBillet(Billet* billet, const string& nomMembre, bool utiliserCoupon);
	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(const string& nomMembre);
	// TODO
	double calculerRevenu() const ;
	// TODO
	int calculerNombreBilletsEnSolde() const ;

	// TODO
	void afficher(ostream& o) const ;
private:
	vector<Membre*> membres_;
	vector<Coupon*> coupons_;
};
#endif // !GESTIONNAIRE_H



